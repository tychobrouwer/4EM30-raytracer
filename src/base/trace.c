/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  04/01/2022 | J.Remmers    | Added different materials / colors (hardcoded)
 *  12/02/2023 | J.Remmers    | Added library structure for materials
 *  17/04/2025 | H.B.G. de Bruijn | updated code for assignment
 *----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <omp.h>
#include "trace.h"
#include "../camera/camera.h"
#include "../materials/materials.h"
#include "../util/color.h"
#include "../util/ray.h"
#include "../util/film.h"
#include "../util/bvh.h"
#include "../light/shadow.h"

#include <omp.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

//------------------------------------------------------------------------------
//  trace: Traces the rays through the scene
//------------------------------------------------------------------------------

void trace

    (Globdat *globdat)

{
  printf("\n  +++ Start tracing +++\n");

  int ix, iy;
  double u, v;

  Ray ray;
  Color color, addColor, bgColor;
  bgColor.red = (int)255 * 0.678;
  bgColor.green = (int)255 * 0.847;
  bgColor.blue = (int)255 * 0.902;

  Intersect intersection;

  BVH *bvh = (BVH *)malloc(sizeof(BVH));
  bvh->nodeCount = 0;

  int total = globdat->mesh.faceCount + globdat->spheres.count;
  buildBVH(bvh, globdat, 0, total);

  int numThreads = 16;
  omp_set_num_threads(numThreads);

  int spp = globdat->cam.samples_per_pixel;
  int strat = globdat->cam.strat;
  int sqrt_spp = (int)sqrt((double)spp);

  if (strat == 1 && sqrt_spp * sqrt_spp != spp)
  {
    if (omp_get_thread_num() == 0)
    {
      printf("Error: samples_per_pixel must be a perfect square for stratified sampling.\n");
    }
    exit(1);
  }

  Vec3 *offsets;
  offsets = (Vec3 *)malloc(SHADOW_SAMPLES * sizeof(Vec3));
  createRandomOffsets(offsets);

#pragma omp parallel for collapse(2) schedule(dynamic, 16) private(ray, u, v, intersection, color, addColor)
  for (ix = 0; ix < globdat->film->width; ix++)
  {
    for (iy = 0; iy < globdat->film->height; iy++)
    {
      color.red = 0;
      color.green = 0;
      color.blue = 0;

      for (int sample = 0; sample < spp; sample++) {
        u = 1.0;
        v = 1.0;

        if (globdat->cam.strat == 1) {
          double jitter_x = rand() / (double)RAND_MAX;
          double jitter_y = rand() / (double)RAND_MAX;

          int sx = sample % sqrt_spp;
          int sy = sample / sqrt_spp;

          u = (sx + jitter_x) / sqrt_spp;
          v = (sy + jitter_y) / sqrt_spp;
        } else {
          if (spp > 1)
          {
            u = (rand() % 1000) / 1000.0;
            v = (rand() % 1000) / 1000.0;
          }
        }

        generateCameraRay(&ray, ix, iy, u, v, &globdat->cam);

        resetIntersect(&intersection);
        traverseBVH(bvh, globdat, &ray, &intersection);

        if (intersection.matID == -1)
        {
          if (globdat->bgimage.loadedFlag == 1)
          {
            int jx, jy;

            mapRayToBGCoordinates(&jx, &jy, ray, globdat);
            addColor = getBGImagePixelValue(&globdat->bgimage, jx, jy);
          }
          else
          {
            addColor = bgColor;
          }
        }
        else
        {
          double lightIntensity = computeIntensity(globdat, bvh, offsets, &ray, &intersection);
          addColor = getColor(lightIntensity, &globdat->materials.mat[intersection.matID]);
        }
        
        color.red += addColor.red;
        color.green += addColor.green;
        color.blue += addColor.blue;
      }

      color.red /= spp;
      color.green /= spp;
      color.blue /= spp;

      storePixelRGB(globdat->film, ix, iy, &color);
    }
  }
}

//------------------------------------------------------------------------------
//  computeIntensity: Computes the intensity of a pixel from the shadows
//------------------------------------------------------------------------------

double computeIntensity(Globdat *globdat, BVH *bvh, Vec3 *offsets, Ray *ray, Intersect *intersection) {
  Vec3 hitPoint = addVector(1.0, &ray->o, intersection->t, &ray->d);
  double lightIntensity = 0.0;

  Intersect shadowHit;
  resetIntersect(&shadowHit);

  Ray shadowRay;
  createShadowRay(globdat, bvh, &shadowRay, &hitPoint, &globdat->sun.d, &intersection->normal);
  traverseBVH(bvh, globdat, &shadowRay, &shadowHit);

  if (shadowHit.matID == -1)
  {
    lightIntensity += fmax(dotProduct(&globdat->sun.d, &intersection->normal), 0.0);
  }

  for (int iSpot = 0; iSpot < globdat->spotlights.count; iSpot++)
  {
    lightIntensity += computeSoftShadow(globdat, bvh, offsets, &hitPoint, &intersection->normal, intersection, iSpot);
  }

  double ambient = 0.05;
  return fmin(ambient + lightIntensity, 1.0);
}

//------------------------------------------------------------------------------
//  mapRayToBGCoordinates: Maps the ray direction to the background image
//                         coordinates
//------------------------------------------------------------------------------

void mapRayToBGCoordinates(int *jx, int *jy, Ray ray, Globdat *globdat)
{
  double x = ray.d.x;
  double y = ray.d.y;
  double z = ray.d.z;

  double theta = acos(z / (sqrt(x * x + y * y + z * z)));

  double phi = atan2(y, x);

  int ny = globdat->bgimage.height;
  int nx = globdat->bgimage.width;

  *jy = (int)(ny * (theta) / PI);
  *jx = (int)(nx * (PI - phi) / (2 * PI));
}
