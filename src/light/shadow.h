#ifndef SHADOW_H
#define SHADOW_H

#include "../base/globalData.h"
#include "../util/vector.h"
#include "../util/ray.h"
#include "../util/bvh.h"

/// Checks if a point is in shadow relative to a light direction (e.g., sun)
void createShadowRay(Globdat* globdat, BVH* bvh, Ray *shadowRay, Vec3* point, Vec3* lightDir, Vec3* normal);

double computeSoftShadow(
    Vec3* hitPoint,
    Vec3* normal,
    Globdat* globdat,
    BVH* bvh,
    Intersect* intersection,
    int lightIndex
);

#endif


