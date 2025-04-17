#include "shadow.h"
#include <math.h>
#include <stdlib.h>
// #include "spotlight.h"


double clamp(double x, double minVal, double maxVal)
{
    if (x < minVal) return minVal;
    if (x > maxVal) return maxVal;
    return x;
}


void createShadowRay(Globdat* globdat, BVH* bvh, Ray *shadowRay, Vec3* point, Vec3* lightDir, Vec3* normal)
{
    Vec3 shadowDir = *lightDir;
    unit(&shadowDir);

    Vec3 bias = multiplyVector(0.001, normal);
    Vec3 shadowOrigin = addVector(1.0, point, 1.0, &bias);

    shadowRay->o = shadowOrigin;
    shadowRay->d = shadowDir;
}

void createRandomOffsets(Vec3* offsets)
{
    for (int i = 0; i < SHADOW_SAMPLES; i++)
    {
        offsets[i].x = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
        offsets[i].y = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
        offsets[i].z = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
    }
}

double computeSoftShadow(
    Vec3* hitPoint,
    Vec3* normal,
    Globdat* globdat,
    BVH* bvh,
    Intersect* intersection,
    Vec3* offsets,
    int lightIndex
    

)
{
    Spotlight* spotlight = &globdat->spotlights.spotlight[lightIndex];

    Vec3 spotlightToHit = subtractVector(1.0, hitPoint, 1.0, &spotlight->coord);
    unit(&spotlightToHit);

    Vec3 target = {0.0, 0.0, 0.0}; // or use actual spotlight direction if you support it
    Vec3 spotlightDir = subtractVector(1.0, &target, 1.0, &spotlight->coord);
    unit(&spotlightDir);

    double angleCos = dotProduct(&spotlightDir, &spotlightToHit);

    if (spotlight->useCutoff && angleCos > spotlight->cosCutoff) {
        return 0.0;
    }

    double falloff = 1.0;
    if (spotlight->useFalloff) {
        double theta = angleCos;
        double epsilon = 0.1; // softness of the edge
        falloff = clamp((theta - spotlight->cosCutoff) / epsilon, 0.0, 1.0);
    }
    
    double sampleLight = 0.0;

    Ray shadowRay;
    Intersect shadowHit;
  
    for (int s = 0; s < SHADOW_SAMPLES; s++)
{
    Vec3 jitteredLightPos = addVector(1.0, &spotlight->coord, 1.0, &offsets[s]);
    Vec3 LightDir = subtractVector(1.0, &jitteredLightPos, 1.0, hitPoint);
    unit(&LightDir);

    resetIntersect(&shadowHit);

    createShadowRay(globdat, bvh, &shadowRay, hitPoint, &LightDir, normal);
    traverseBVH(bvh, globdat, &shadowRay, &shadowHit);

    if (shadowHit.matID == -1)
    {
        double dot = fmax(dotProduct(&LightDir, normal), 0.0);
        sampleLight += dot;
    }
}

    double result = (sampleLight / SHADOW_SAMPLES) * falloff * spotlight->intensity;
    if (result > 0.01)
        // printf("Spotlight %d hits with %.4f light\n", lightIndex, result);

    return result;
    
}

