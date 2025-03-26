#ifndef UTIL_BVH_H
#define UTIL_BVH_H

#include "vector.h"
#include "ray.h"
#include "../shapes/shapes.h"
#include "../shapes/mesh.h"
#include "../shapes/spheres.h"

#define MAX_BVH_NODES 1000000

typedef struct
{
  Vec3 min;
  Vec3 max;
} AABB;


typedef struct {
  AABB bbox;
  int leftChild, rightChild;
  int firstObject, objectCount;
  int isLeaf;
} BVHNode;


typedef struct {
  BVHNode nodes[MAX_BVH_NODES];
  int nodeCount;
} BVH;


typedef struct {
  int index;
  int isPrimitive;
  Vec3 centroid;
} PrimitiveInfo;


AABB computeFaceAABB(Face* face);

AABB computeSphereAABB(Sphere* sphere);

Vec3 computeCentroidAABB(AABB* aabb);

int comparePrimitives(const void* a, const void* b);

int buildBVH(BVH *bvh, Globdat *globdat, int first, int count);

int intersectAABB(Ray *ray, AABB *aabb, Vec3 *invDir);

void traverseBVH(BVH* bvh, Globdat *globdat, Ray* ray, Intersect* intersect, int nodeIndex, Vec3* invDir);

#endif
