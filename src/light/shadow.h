#ifndef SHADOW_H
#define SHADOW_H

#include "../base/globalData.h"
#include "../util/vector.h"
#include "../util/ray.h"
#include "../util/bvh.h"

#define SHADOW_SAMPLES 5
#define SHADOW_JITTER 0.05
#define SHADOW_RADIUS 0.05 // Jitter radius for soft shadow sampling


//------------------------------------------------------------------------------
//  createShadowRay: Initializes a shadow ray for hard shadow computation.
//
//  Arguments:
//      globdat     : Global scene data (materials, lights, etc.)
//      bvh         : Pointer to the Bounding Volume Hierarchy for intersection tests
//      shadowRay   : Pointer to the ray that will be created
//      point       : The point on the surface being shaded
//      lightDir    : The direction towards the light source
//      normal      : The surface normal at the hit point
//
//  Description:
//      This function constructs a ray originating from the surface point and
//      pointing in the direction of the light. The ray is slightly offset along
//      the normal to avoid self-intersections (shadow acne).
//------------------------------------------------------------------------------


void createShadowRay(Globdat* globdat, BVH* bvh, Ray *shadowRay, Vec3* point, Vec3* lightDir, Vec3* normal);


//------------------------------------------------------------------------------
//  createRandomOffsets: Generates random jitter offsets for soft shadow rays.
//
//  Arguments:
//      offsets     : Pointer to an array of Vec3s where random offsets will be stored
//
//  Description:
//      This function fills the offsets array with small randomized direction vectors,
//      used to simulate area light soft shadows through multiple shadow ray sampling.
//------------------------------------------------------------------------------


void createRandomOffsets(Vec3* offsets);


//------------------------------------------------------------------------------
//  computeSoftShadow: Computes soft shadow intensity at a point using multiple rays.
//
//  Arguments:
//      hitPoint        : The point on the surface being shaded
//      normal          : Surface normal at the hit point
//      globdat         : Global scene data (lights, materials, etc.)
//      bvh             : Pointer to the Bounding Volume Hierarchy for intersections
//      intersection    : Intersection data at the hit point
//      offsets         : Precomputed random offsets for soft shadow sampling
//      lightIndex      : Index of the light source being considered
//
//  Return:
//      double          : A factor between 0 and 1 indicating light visibility,
//                        where 0 = fully shadowed, 1 = fully lit.
//
//  Description:
//      This function casts multiple jittered shadow rays toward the light source,
//      taking into account occlusions. It averages the visibility across all
//      samples to simulate soft shadowing effects from an area light.
//------------------------------------------------------------------------------


double computeSoftShadow(
    Globdat* globdat,
    BVH* bvh,
    Vec3* offsets,
    Vec3* hitPoint,
    Vec3* normal,
    Intersect* intersection,
    int lightIndex
);

#endif


