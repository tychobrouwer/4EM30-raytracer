#include "shadow.h"
#include <math.h>

void createShadowRay(Globdat* globdat, BVH* bvh, Ray *shadowRay, Vec3* point, Vec3* lightDir, Vec3* normal)
{
    Vec3 shadowDir = *lightDir;
    unit(&shadowDir);

    Vec3 bias = multiplyVector(0.001, normal);
    Vec3 shadowOrigin = addVector(1.0, point, 1.0, &bias);

    shadowRay->o = shadowOrigin;
    shadowRay->d = shadowDir;
}
