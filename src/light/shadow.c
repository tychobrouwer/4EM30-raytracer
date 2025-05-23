#include "shadow.h"
#include <math.h>
#include <stdlib.h>


//------------------------------------------------------------------------------
//  createShadowRay: Create shadow ray from light 
//------------------------------------------------------------------------------

void createShadowRay(Globdat *globdat, BVH *bvh, Ray *shadowRay, Vec3 *point, Vec3 *lightDir, Vec3 *normal)
{
    unit(lightDir);

    Vec3 bias = multiplyVector(0.001, normal);
    Vec3 shadowOrigin = addVector(1.0, point, 1.0, &bias);

    shadowRay->o = shadowOrigin;
    shadowRay->d = *lightDir;
}

//------------------------------------------------------------------------------
//  createRandomOffsets: Create random offsets for shadow sampling
//------------------------------------------------------------------------------


void createRandomOffsets(Vec3 *offsets)
{
    for (int i = 0; i < SHADOW_SAMPLES; i++)
    {
        offsets[i].x = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
        offsets[i].y = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
        offsets[i].z = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
    }
}

//------------------------------------------------------------------------------
//  computeSoftShadow: Computes the soft shadow contribution from a spotlight
//------------------------------------------------------------------------------

double computeSoftShadow(
    Globdat *globdat,
    BVH *bvh,
    Vec3 *offsets,
    Vec3 *hitPoint,
    Vec3 *normal,
    Intersect *intersection,
    int lightIndex)
{
   

    Spotlight *spotlight = &globdat->spotlights.spotlight[lightIndex];

    Vec3 hitToSpotlight = addVector(1.0, &spotlight->coord, -1.0, hitPoint);
    unit(&hitToSpotlight);

    double angleCos = dotProduct(&spotlight->dir, &hitToSpotlight);

    if (angleCos < 0.0)
        angleCos = -angleCos;

    if (angleCos < spotlight->cosCutoff)
        return 0.0;

    double falloff = fmax(fmin((angleCos - spotlight->cosCutoff) / spotlight->sharpness, 0.0), 1.0);

    double sampleLight = 0.0;
    Ray shadowRay;
    Intersect shadowHit;

    for (int s = 0; s < SHADOW_SAMPLES; s++)
    {
        Vec3 jitteredLightPos = addVector(1.0, &spotlight->coord, 1.0, &offsets[s]);
        Vec3 lightDir = addVector(1.0, &jitteredLightPos, -1.0, hitPoint);
        unit(&lightDir);

        resetIntersect(&shadowHit);

        createShadowRay(globdat, bvh, &shadowRay, hitPoint, &lightDir, normal);
        traverseBVH(bvh, globdat, &shadowRay, &shadowHit);

        if (shadowHit.matID == -1)
        {
            double dot = fmax(dotProduct(&lightDir, normal), 0.0);
            sampleLight += dot;
        }
    }

    double result = (sampleLight / SHADOW_SAMPLES) * falloff * spotlight->intensity;

    return result;
}
