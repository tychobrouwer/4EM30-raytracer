#ifndef UTIL_BVH_H
#define UTIL_BVH_H

#include "vector.h"
#include "ray.h"
#include "../shapes/shapes.h"
#include "../shapes/mesh.h"
#include "../shapes/spheres.h"

#define MAX_BVH_NODES 1000000


//------------------------------------------------------------------------------
//  Declaration of the AABB axis-aligned bounding box structure
//------------------------------------------------------------------------------


typedef struct
{
  Vec3 min;
  Vec3 max;
} AABB;


//------------------------------------------------------------------------------
//  Declaration of the BVH node structure
//------------------------------------------------------------------------------


typedef struct {
  AABB bbox;
  int leftChild, rightChild;
  int firstObject, objectCount;
  int isLeaf;
} BVHNode;


//------------------------------------------------------------------------------
//  Declaration of the BVH structure
//------------------------------------------------------------------------------


typedef struct {
  BVHNode nodes[MAX_BVH_NODES];
  int nodeCount;
} BVH;


//------------------------------------------------------------------------------
//  Declaration of the PrimitiveInfo structure used for combining spheres and
//  faces in the BVH needed for sorting
//------------------------------------------------------------------------------


typedef struct {
  int index;
  int isPrimitive;
  Vec3 centroid;
} PrimitiveInfo;


//------------------------------------------------------------------------------
//  computeFaceAABB: Computes the AABB of a face
//
//  Arguments:
//      face    : Pointer to the face
//
//  Return:
//      AABB    : the axis-aligned bounding box (AABB) of the face
//
//------------------------------------------------------------------------------


AABB computeFaceAABB

  ( Face*         face );


//------------------------------------------------------------------------------
//  computeSphereAABB: Computes the AABB of a sphere
//
//  Arguments:
//      sphere    : Pointer to the sphere
//
//  Return:
//      AABB    : the axis-aligned bounding box (AABB) of the sphere
//
//------------------------------------------------------------------------------


AABB computeSphereAABB

  ( Sphere*       sphere );


//------------------------------------------------------------------------------
//  computeCentroidAABB: Computes the centroid of an AABB
//
//  Arguments:
//      aabb    : Pointer to the axis-aligned bounding box (AABB)
//
//  Return:
//      Vec3    : the centroid of the AABB
//
//------------------------------------------------------------------------------


Vec3 computeCentroidAABB

  ( AABB*         aabb );


//------------------------------------------------------------------------------
//  comparePrimitives: Compares two primitives based on their centroids
//
//  Arguments:
//      a    : Pointer to the first primitive
//      b    : Pointer to the second primitive
//
//  Return:
//      int  : the result of the comparison
//
//------------------------------------------------------------------------------


int comparePrimitives

  ( const void*   a ,
    const void*   b );


//------------------------------------------------------------------------------
//  buildBVH: Builds the BVH tree
//
//  Arguments:
//      bvh       : Pointer to the BVH tree
//      globdat   : Pointer to the global data
//      first     : Index of the first primitive
//      count     : Number of primitives
//
//  Return:
//      int       : the index of the root node
//
//------------------------------------------------------------------------------


int buildBVH

  ( BVH           *bvh     ,
    Globdat       *globdat ,
    int           first    ,
    int           count    );


//------------------------------------------------------------------------------
//  intersectAABB: Intersects a ray with an AABB
//
//  Arguments:
//      ray       : Pointer to the ray
//      aabb      : Pointer to the axis-aligned bounding box (AABB)
//      invDir    : Pointer to the inverse direction of the ray
//
//  Return:
//      int       : 1 if the ray intersects the AABB, 0 otherwise
//
//------------------------------------------------------------------------------


int intersectAABB

  ( Ray*          ray    ,
    AABB*         aabb   ,
    Vec3*         invDir );


//------------------------------------------------------------------------------
//  traverseBVH: Traverses the BVH tree
//
//  Arguments:
//      bvh        : Pointer to the BVH tree
//      globdat    : Pointer to the global data
//      ray        : Pointer to the ray
//      intersect  : Pointer to the intersection
//      nodeIndex  : Index of the current node
//      invDir     : Pointer to the inverse direction of the ray
//
//------------------------------------------------------------------------------


void traverseBVH

  ( BVH*          bvh          ,
    Globdat*      globdat      ,
    Ray*          ray          ,
    Intersect*    intersection ,
    int           nodeIndex    ,
    Vec3*         invDir       );


#endif
