#ifndef SHADOW_H
#define SHADOW_H

#include "../base/globalData.h"
#include "../util/vector.h"
#include "../util/ray.h"
#include "../util/bvh.h"

#define SHADOW_SAMPLES 3
#define SHADOW_JITTER 0.005
#define SHADOW_RADIUS 0.005 // Jitter radius for soft shadow sampling

/// Checks if a point is in shadow relative to a light direction (e.g., sun)
void createShadowRay(Globdat* globdat, BVH* bvh, Ray *shadowRay, Vec3* point, Vec3* lightDir, Vec3* normal);

void createRandomOffsets(Vec3* offsets);

double computeSoftShadow(
    Vec3* hitPoint,
    Vec3* normal,
    Globdat* globdat,
    BVH* bvh,
    Intersect* intersection,
    Vec3* offsets,
    int lightIndex
);

#endif


