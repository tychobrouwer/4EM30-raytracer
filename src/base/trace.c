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
 *
 *----------------------------------------------------------------------------*/

#include "trace.h"
#include "../camera/camera.h"
#include "../materials/materials.h"
#include "../shapes/shapes.h"
#include "../util/color.h"
#include "../util/ray.h"
#include "../util/film.h"
#include "../util/bvh.h"
#include "../light/shadow.h" // shadow implementation

#include <omp.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

//------------------------------------------------------------------------------
//  trace: Traces the rays through the scene
//------------------------------------------------------------------------------

void trace(Globdat *globdat)

{
  printf("\n  +++ Start tracing +++\n");

  int ix, iy;

  Ray ray;
  Color col;

  Color bgcol;
  bgcol.red = (int)255 * 0.678;
  bgcol.green = (int)255 * 0.847;
  bgcol.blue = (int)255 * 0.902;

  Intersect intersection;

  BVH *bvh = (BVH *)malloc(sizeof(BVH));
  bvh->nodeCount = 0;

  int total = globdat->mesh.faceCount + globdat->spheres.count;
  buildBVH(bvh, globdat, 0, total);

  int numThreads = 16;
  omp_set_num_threads(numThreads);

  Vec3 *offsets;
  offsets = (Vec3 *)malloc(SHADOW_SAMPLES * sizeof(Vec3));
  createRandomOffsets(offsets);

#pragma omp parallel for collapse(2) schedule(dynamic, 16) private(ray, intersection, col)
  for (ix = 0; ix < globdat->film->width; ix++)
  {
    for (iy = 0; iy < globdat->film->height; iy++)
    {
      generateRay(&ray, ix, iy, &globdat->cam);
      resetIntersect(&intersection);
      traverseBVH(bvh, globdat, &ray, &intersection);

      if (intersection.matID == -1)
      {
        if (globdat->bgimage.loadedFlag == 1)
        {
          int jx, jy;
          mapRayToBGCoordinates(&jx, &jy, ray, globdat);
          col = getBGImagePixelValue(&globdat->bgimage, jx, jy);
        }
        else
        {
          col = bgcol;
        }
      }
      else
      {
        Vec3 hitPoint = addVector(1.0, &ray.o, intersection.t, &ray.d);
        double totalLight = 0.0;

        // SUNLIGHT

        Intersect shadowHit;
        resetIntersect(&shadowHit);

        Ray shadowRay;
        createShadowRay(globdat, bvh, &shadowRay, &hitPoint, &globdat->sun.d, &intersection.normal);
        traverseBVH(bvh, globdat, &shadowRay, &shadowHit);

        if (shadowHit.matID == -1)
        {
          totalLight += fmax(dotProduct(&globdat->sun.d, &intersection.normal), 0.0);
        }

        // --SPOTLIGHTS--

        for (int iSpot = 0; iSpot < globdat->spotlights.count; iSpot++)
        {
          totalLight += computeSoftShadow(&hitPoint, &intersection.normal, globdat, bvh, &intersection, offsets, iSpot);

          // printf("Calling spotlight %d\n", iSpot);
        }

        // Final lighting and color
        double ambient = 0.05;
        double finalLight = fmin(ambient + totalLight, 1.0);
        Color baseColor = getColor(1.0, &globdat->materials.mat[intersection.matID]);
        col.red = (int)(baseColor.red * finalLight);
        col.green = (int)(baseColor.green * finalLight);
        col.blue = (int)(baseColor.blue * finalLight);
        // Optional: clamp
        col.red = fmin(col.red, 255);
        col.green = fmin(col.green, 255);
        col.blue = fmin(col.blue, 255);
      }

      storePixelRGB(globdat->film, ix, iy, &col);
    }
  }

  free(bvh);
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
