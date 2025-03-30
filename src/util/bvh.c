#include "bvh.h"

#include <stdlib.h>
#include <float.h>

#define PRIMITIVE_FACE   0
#define PRIMITIVE_SPHERE 1

//------------------------------------------------------------------------------
//  computeFaceAABB: Computes the AABB of a face
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//  computeSphereAABB: Computes the AABB of a sphere
//------------------------------------------------------------------------------

AABB computeSphereAABB(Sphere *sphere)
{
  Vec3 radiusVec = {sphere->radius, sphere->radius, sphere->radius};

  AABB bbox;
  bbox.min = subtractVector(1.0, &sphere->centre, 1.0, &radiusVec);
  bbox.max = addVector(1.0, &sphere->centre, 1.0, &radiusVec);
  return bbox;
}

//------------------------------------------------------------------------------
//  computeCentroidAABB: Computes the centroid of an AABB
//------------------------------------------------------------------------------

Vec3 computeCentroidAABB(AABB *aabb)
{
  Vec3 centroid;

  centroid.x = (aabb->min.x + aabb->max.x) / 2.0;
  centroid.y = (aabb->min.y + aabb->max.y) / 2.0;
  centroid.z = (aabb->min.z + aabb->max.z) / 2.0;

  return centroid;
}

//------------------------------------------------------------------------------
//  comparePrimitives: Compares two primitives
//------------------------------------------------------------------------------

static int splitAxis = 0;

int comparePrimitives(const void *a, const void *b)
{
  const PrimitiveInfo *infoA = (const PrimitiveInfo *)a;
  const PrimitiveInfo *infoB = (const PrimitiveInfo *)b;

  double centroidA, centroidB;
  if (splitAxis == 0)
  {
    centroidA = infoA->centroid.x;
    centroidB = infoB->centroid.x;
  }
  else if (splitAxis == 1)
  {
    centroidA = infoA->centroid.y;
    centroidB = infoB->centroid.y;
  }
  else
  {
    centroidA = infoA->centroid.z;
    centroidB = infoB->centroid.z;
  }

  if (centroidA < centroidB)
    return -1;
  else if (centroidA > centroidB)
    return 1;

  return 0;
}

//------------------------------------------------------------------------------
//  buildBVH: Builds the BVH tree
//------------------------------------------------------------------------------


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

  for (int i = 0; i < count; i++)
  {
    int objIndex = first + i;
    primitives[i].index = objIndex;

    AABB aabb;
    if (objIndex < globdat->mesh.faceCount)
    {
      primitives[i].isPrimitive = PRIMITIVE_FACE;

      Face face;
      getFace(&face, objIndex, &globdat->mesh);
      aabb = computeFaceAABB(&face);
    }
    else
    {
      primitives[i].isPrimitive = PRIMITIVE_SPHERE;
      int sphereIndex = objIndex - globdat->mesh.faceCount;

      aabb = computeSphereAABB(&globdat->spheres.sphere[sphereIndex]);
    }

    primitives[i].centroid = computeCentroidAABB(&aabb);

    node->bbox.min = minVector(1.0, &node->bbox.min, 1.0, &aabb.min);
    node->bbox.max = maxVector(1.0, &node->bbox.max, 1.0, &aabb.max);
  }

  if (count <= 4)
  {
    node->firstObject = first;
    node->objectCount = count;
    node->isLeaf = 1;
    free(primitives);
    return nodeIndex;
  }

  Vec3 size = subtractVector(1.0, &node->bbox.max, 1.0, &node->bbox.min);
  if (size.x > size.y && size.x > size.z)
  {
    splitAxis = 0; // X-axis
  }
  else if (size.y > size.z)
  {
    splitAxis = 1; // Y-axis
  }
  else
  {
    splitAxis = 2; // Z-axis
  }

  qsort(primitives, count, sizeof(PrimitiveInfo), comparePrimitives);

  int mid = count / 2;

  node->leftChild = buildBVH(bvh, globdat, first, mid);
  node->rightChild = buildBVH(bvh, globdat, first + mid, count - mid);

  node->isLeaf = 0;

  free(primitives);

  return nodeIndex;
}


//------------------------------------------------------------------------------
//  intersectAABB: Intersects a ray with an AABB
//------------------------------------------------------------------------------

int intersectAABB(Ray *ray, AABB *aabb, const Vec3 *invDir, const int dirIsNeg[3], double maxDist)
{
  double tmin = ((dirIsNeg[0] ? aabb->max.x : aabb->min.x) - ray->o.x) * invDir->x;
  double tmax = ((dirIsNeg[0] ? aabb->min.x : aabb->max.x) - ray->o.x) * invDir->x;
    
  double tymin = ((dirIsNeg[1] ? aabb->max.y : aabb->min.y) - ray->o.y) * invDir->y;
  double tymax = ((dirIsNeg[1] ? aabb->min.y : aabb->max.y) - ray->o.y) * invDir->y;
  
  if (tmin > tymax || tymin > tmax || tmin > maxDist) return 0;
  
  if (tymin > tmin) tmin = tymin;
  if (tymax < tmax) tmax = tymax;
  
  double tzmin = ((dirIsNeg[2] ? aabb->max.z : aabb->min.z) - ray->o.z) * invDir->z;
  double tzmax = ((dirIsNeg[2] ? aabb->min.z : aabb->max.z) - ray->o.z) * invDir->z;
  
  if (tmin > tzmax || tzmin > tmax || tzmin > maxDist) return 0;
  
  return 1;
}

//------------------------------------------------------------------------------
//  traverseBVH: Traverses the BVH tree
//------------------------------------------------------------------------------

void traverseBVH(BVH *bvh, Globdat *globdat, Ray *ray, Intersect *intersect)
{
  int nodeStack[1028];
  int stackPtr = 0;
  int nodeIndex = 0;

  const Vec3 invDir = {1.0 / ray->d.x, 1.0 / ray->d.y, 1.0 / ray->d.z};
  const int dirIsNeg[3] = {invDir.x < 0, invDir.y < 0, invDir.z < 0};

  double maxDist = (intersect->t < DBL_MAX) ? intersect->t : DBL_MAX;

  while (true)
  {
    BVHNode *node = &bvh->nodes[nodeIndex];
    

    if (intersectAABB(ray, &node->bbox, &invDir, dirIsNeg, maxDist))
    {
      if (node->isLeaf)
      {
        for (int i = node->firstObject; i < node->firstObject + node->objectCount; i++)
        {
          if (intersect->t < maxDist) {
            maxDist = intersect->t;
          }

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

        if (stackPtr == 0)
          break;
        nodeIndex = nodeStack[--stackPtr];
      }
      else
      {
        nodeIndex = node->leftChild;
        nodeStack[stackPtr++] = node->rightChild;
      }
    }
    else
    {
      if (stackPtr == 0)
        break;
      nodeIndex = nodeStack[--stackPtr];
    }
  }
}
