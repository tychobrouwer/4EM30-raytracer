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

  if (count <= 2)
  {
    node->firstObject = first;
    node->objectCount = count;
    node->isLeaf = 1;
    free(primitives);
    return nodeIndex;
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

int intersectAABB(Ray *ray, AABB *aabb, Vec3 *invDir)
{
  const double* bounds[2] = {&aabb->min.x, &aabb->max.x};
  const double* origin = &ray->o.x;
  const double* inv = &invDir->x;

  double t1, t2;
  double minT = 0.0f, maxT = DBL_MAX;

  for (int i = 0; i < 3; i++) {
    t1 = (bounds[0][i] - origin[i]) * inv[i];
    t2 = (bounds[1][i] - origin[i]) * inv[i];

    if (inv[i] < 0.0f) {
      double temp = t1;
      t1 = t2;
      t2 = temp;
    }

    minT = (t1 > minT) ? t1 : minT;
    maxT = (t2 < maxT) ? t2 : maxT;

    if (maxT <= minT) return 0;
  }

  return 1;
}


//------------------------------------------------------------------------------
//  traverseBVH: Traverses the BVH tree
//------------------------------------------------------------------------------


void traverseBVH(BVH *bvh, Globdat *globdat, Ray *ray, Intersect *intersect, int startNodeIndex, Vec3 *invDir)
{ 
  int nodeStack[64];  // Fixed size stack, adjust as needed
  int stackPtr = 0;
  nodeStack[stackPtr++] = startNodeIndex;

  while (stackPtr > 0) {
    int nodeIndex = nodeStack[--stackPtr];
    BVHNode *node = &bvh->nodes[nodeIndex];

    if (!intersectAABB(ray, &node->bbox, invDir)) {    
      continue;
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
    } else {
      nodeStack[stackPtr++] = node->rightChild;
      nodeStack[stackPtr++] = node->leftChild;
    }
  }
}
