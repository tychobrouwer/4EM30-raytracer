#include "bvh.h"

#include <stdlib.h>
#include <float.h>

AABB computeFaceAABB(Face *face)
{
  AABB bbox;
  bbox.min = bbox.max = face->vertices[0];

  for (int i = 1; i < face->vertexCount; i++)
  {
    Vec3 v = face->vertices[i];

    bbox.min = minVector(1.0, &bbox.min, 1.0, &v);
    bbox.max = maxVector(1.0, &bbox.max, 1.0, &v);
  }

  return bbox;
}

AABB computeSphereAABB(Sphere *sphere)
{
  Vec3 radiusVec = {sphere->radius, sphere->radius, sphere->radius};

  AABB bbox;
  bbox.min = subtractVector(1.0, &sphere->centre, 1.0, &radiusVec);
  bbox.max = addVector(1.0, &sphere->centre, 1.0, &radiusVec);
  return bbox;
}

Vec3 computeCentroidAABB(AABB *aabb)
{
  Vec3 centroid;

  centroid.x = (aabb->min.x + aabb->max.x) / 2.0;
  centroid.y = (aabb->min.y + aabb->max.y) / 2.0;
  centroid.z = (aabb->min.z + aabb->max.z) / 2.0;

  return centroid;
}

int comparePrimitives(const void *a, const void *b)
{
  const PrimitiveInfo *infoA = (const PrimitiveInfo *)a;
  const PrimitiveInfo *infoB = (const PrimitiveInfo *)b;

  if (infoA->centroid.x < infoB->centroid.x)
    return -1;
  else if (infoA->centroid.x > infoB->centroid.x)
    return 1;

  if (infoA->centroid.y < infoB->centroid.y)
    return -1;
  else if (infoA->centroid.y > infoB->centroid.y)
    return 1;

  if (infoA->centroid.z < infoB->centroid.z)
    return -1;
  else if (infoA->centroid.z > infoB->centroid.z)
    return 1;

  return 0;
}

int buildBVH(BVH *bvh, Globdat *globdat, int first, int count)
{
  if (bvh->nodeCount >= MAX_BVH_NODES)
  {
    printf("ERROR: Maximum BVH node count reached\n");
    return -1;
  }

  int nodeIndex = bvh->nodeCount++;
  BVHNode *node = &bvh->nodes[nodeIndex];

  node->bbox.min = (Vec3){DBL_MAX, DBL_MAX, DBL_MAX};
  node->bbox.max = (Vec3){-DBL_MAX, -DBL_MAX, -DBL_MAX};

  PrimitiveInfo *primitives = (PrimitiveInfo *)malloc(count * sizeof(PrimitiveInfo));
  if (!primitives)
  {
    printf("ERROR: Memory allocation failed for primitives\n");
    return -1;
  }

  for (int i = 0; i < count; i++)
  {
    int objIndex = first + i;
    primitives[i].index = objIndex;

    AABB aabb;
    if (objIndex < globdat->mesh.faceCount)
    {
      primitives[i].isPrimitive = 0;

      Face face;
      getFace(&face, objIndex, &globdat->mesh);
      aabb = computeFaceAABB(&face);
    }
    else
    {
      primitives[i].isPrimitive = 1;
      int sphereIndex = objIndex - globdat->mesh.faceCount;

      if (sphereIndex >= globdat->spheres.count)
      {
        printf("ERROR: Sphere index out of bounds: %d\n", sphereIndex);
        free(primitives);
        return -1;
      }

      aabb = computeSphereAABB(&globdat->spheres.sphere[sphereIndex]);
    }

    primitives[i].centroid = computeCentroidAABB(&aabb);

    node->bbox.min = minVector(1.0, &node->bbox.min, 1.0, &aabb.min);
    node->bbox.max = maxVector(1.0, &node->bbox.max, 1.0, &aabb.max);
  }

  if (count <= 2)
  {
    node->firstObject = first;
    node->objectCount = count;
    node->isLeaf = 1;
    free(primitives);
    return nodeIndex;
  }

  Vec3 size = subtractVector(1.0, &node->bbox.max, 1.0, &node->bbox.min);
  if (size.x == 0 && size.y == 0 && size.z == 0) {
    printf("Degenerate AABB detected\n");
    return -1;
  }

  qsort(primitives, count, sizeof(PrimitiveInfo), comparePrimitives);

  int mid = count / 2;

  node->leftChild = buildBVH(bvh, globdat, first, mid);
  node->rightChild = buildBVH(bvh, globdat, first + mid, count - mid);

  node->isLeaf = 0;

  free(primitives);


  return nodeIndex;
}

int intersectAABB(Ray *ray, AABB *aabb)
{
  double invDirX = ray->d.x == 0 ? 1e30 : 1.0 / ray->d.x;
  double invDirY = ray->d.y == 0 ? 1e30 : 1.0 / ray->d.y;
  double invDirZ = ray->d.z == 0 ? 1e30 : 1.0 / ray->d.z;

  double tx1 = (aabb->min.x - ray->o.x) * invDirX;
  double tx2 = (aabb->max.x - ray->o.x) * invDirX;
  double ty1 = (aabb->min.y - ray->o.y) * invDirY;
  double ty2 = (aabb->max.y - ray->o.y) * invDirY;
  double tz1 = (aabb->min.z - ray->o.z) * invDirZ;
  double tz2 = (aabb->max.z - ray->o.z) * invDirZ;

  if (ray->d.x == 0 && (ray->o.x < aabb->min.x || ray->o.x > aabb->max.x))
    return 0;
  if (ray->d.y == 0 && (ray->o.y < aabb->min.y || ray->o.y > aabb->max.y))
    return 0;
  if (ray->d.z == 0 && (ray->o.z < aabb->min.z || ray->o.z > aabb->max.z))
    return 0;

  double tmin = fmin(tx1, tx2);
  double tmax = fmax(tx1, tx2);
  tmin = fmax(tmin, fmin(ty1, ty2));
  tmax = fmin(tmax, fmax(ty1, ty2));
  tmin = fmax(tmin, fmin(tz1, tz2));
  tmax = fmin(tmax, fmax(tz1, tz2));

  return tmax >= tmin && tmax > 0;
}

void traverseBVH(BVH *bvh, Globdat *globdat, Ray *ray, Intersect *intersect, int nodeIndex)
{
  BVHNode *node = &bvh->nodes[nodeIndex];

  if (!intersectAABB(ray, &node->bbox)) {    
    return;
  }

  if (node->isLeaf)
  {
    for (int i = node->firstObject; i < node->firstObject + node->objectCount; i++)
    {
      if (i < globdat->mesh.faceCount)
      {
        Face face;
        getFace(&face, i, &globdat->mesh);
        calcFaceIntersection(intersect, ray, &face);
      }
      else
      {
        int iSphere = i - globdat->mesh.faceCount;
        calcSphereIntersection(intersect, ray, &globdat->spheres.sphere[iSphere]);
      }
    }
    return;
  }

  traverseBVH(bvh, globdat, ray, intersect, node->leftChild);
  traverseBVH(bvh, globdat, ray, intersect, node->rightChild);
}
