#include "shadow.h"
#include <math.h>
#include <stdlib.h>
// #include "spotlight.h"

#define SHADOW_SAMPLES 32
#define SHADOW_JITTER 0.05
#define SHADOW_RADIUS 0.05 // Jitter radius for soft shadow sampling

void createShadowRay(Globdat* globdat, BVH* bvh, Ray *shadowRay, Vec3* point, Vec3* lightDir, Vec3* normal)
{
    Vec3 shadowDir = *lightDir;
    unit(&shadowDir);

    Vec3 bias = multiplyVector(0.001, normal);
    Vec3 shadowOrigin = addVector(1.0, point, 1.0, &bias);

    shadowRay->o = shadowOrigin;
    shadowRay->d = shadowDir;
}

double computeSoftShadow(
    Vec3* hitPoint,
    Vec3* normal,
    Globdat* globdat,
    BVH* bvh,
    Intersect* intersection,
    int lightIndex
)
{
    Spotlight* spotlight = &globdat->spotlights.spotlight[lightIndex];

    // printf(">>> computeSoftShadow called for spotlight %d\n", lightIndex);

    // Direction from spotlight to hitpoint (used to simulate cone direction)
    Vec3 spotlightToHit = subtractVector(1.0, hitPoint, 1.0, &spotlight->coord);
    unit(&spotlightToHit);

    // Simulated spotlight direction = towards object
    // Assume ideal direction is down Z axis, so we simulate a cone around that
    // double angleCos = spotlightToHit.z;  // <- Z axis aligned spotlight cone
    // if (angleCos < cos(spotlight->cutoff)) return 0.0;
    // printf("Spotlight %d angleCos = %.4f, cutoffCos = %.4f\n", lightIndex, angleCos, cos(spotlight->cutoff));

    double angleCos = 1.0;  // Temporarily bypass cone check
    

    double falloff = 1.0; // for debugging        
    // double falloff = pow(angleCos, spotlight->falloffSharpness); // custom parameter
    falloff = fmin(fmax(falloff, 0.0), 1.0);
    

    double sampleLight = 0.0;

    for (int s =0; s<SHADOW_SAMPLES; s++)

    {
        //Jitter the spotlight position, to simulate area light
        Vec3 offset;
        offset.x = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
        offset.y = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);
        offset.z = SHADOW_RADIUS * ((double)rand() / RAND_MAX - 0.5);

        Vec3 jitteredLightPos = addVector(1.0, &spotlight->coord, 1.0, &offset);
        Vec3 LightDir = subtractVector(1.0, &jitteredLightPos, 1.0, hitPoint);
        unit(&LightDir);

        Ray shadowRay;
        Intersect shadowHit;
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
        printf("Spotlight %d hits with %.4f light\n", lightIndex, result);

    return result;
    
}

