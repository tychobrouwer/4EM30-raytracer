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

#include <stdlib.h>
#include <omp.h>
#include "trace.h"
#include "../camera/camera.h"
#include "../materials/materials.h"
#include "../shapes/shapes.h"
#include "../util/color.h"
#include "../util/ray.h"
#include "../util/film.h"
#include "../util/bvh.h"
#include "../light/shadow.h"    // shadow implementation

#include <omp.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

//------------------------------------------------------------------------------
//  trace: Traces the rays through the scene
//------------------------------------------------------------------------------


void trace

  ( Globdat*  globdat )

{
  printf("\n  +++ Start tracing +++\n");
  
  int ix,iy;
  double u,v;
  
  Ray   ray;
  Color col;

  Color bgcol;
  bgcol.red   = (int)255*0.678;
  bgcol.green = (int)255*0.847;
  bgcol.blue  = (int)255*0.902;

  Intersect intersection;

  BVH *bvh;
  bvh = (BVH*)malloc(sizeof(BVH));
  bvh->nodeCount = 0;

  int total = globdat->mesh.faceCount + globdat->spheres.count;
  buildBVH(bvh, globdat, 0, total);

  int numThreads = 16;
  omp_set_num_threads(numThreads);

  #pragma omp parallel for collapse(2) schedule(dynamic, 16) private(ray, intersection, col)
  for ( ix = 0 ; ix < globdat->film->width ; ix++ )
  {
    for ( iy = 0 ; iy < globdat->film->height ; iy++ )
    {
      col.red = 0;
      col.green = 0;
      col.blue = 0;
      
      for (int sample = 0; sample < globdat->cam.samples_per_pixel; sample++)
      {
      // Generate random u, v values between 0 and 1
      // u = drand48();
      // v = drand48();
      
      u = (rand() % 1000) / 1000.0;  // Random number between 0 and 1
      v = (rand() % 1000) / 1000.0;  // Random number between 0 and 1

      generateRay( &ray , ix , iy , u, v, &globdat->cam );
      
      resetIntersect( &intersection );
      
      traverseBVH(bvh, globdat, &ray, &intersection);
           
      if ( intersection.matID == -1 )
      {
        if ( globdat->bgimage.loadedFlag == 1 )
        {
          int jx, jy;

          mapRayToBGCoordinates(&jx, &jy, ray, globdat);
          col = getBGImagePixelValue( &globdat->bgimage , jx , jy );
          double x = ray.d.x;
          double y = ray.d.y;
          double z = ray.d.z;
         
          int jx,jy;
                
          double theta = acos(z / ( sqrt(x*x + y*y + z*z)));
        
          double phi   = atan2(y, x);
                
          int ny = globdat->bgimage.height;
          int nx = globdat->bgimage.width;        
        
          jy = (int)ny*(theta)/3.14;
          jx = (int)nx*(3.14-phi)/6.28;
              
          Color bgCol = getBGImagePixelValue( &globdat->bgimage , jx , jy );
          col.red += bgCol.red;
          col.green += bgCol.green;
          col.blue += bgCol.blue;
        }
        else
        {
          col = bgcol;
        }
      }
      else      
      {
        Vec3 hitPoint = addVector(1.0, &ray.o, intersection.t, &ray.d);
            
        Ray shadowRay;
        createShadowRay(globdat, bvh, &shadowRay, &hitPoint, &globdat->sun.d, &intersection.normal);
      
        Intersect shadowHit;
        resetIntersect(&shadowHit);
      
        traverseBVH(bvh, globdat, &shadowRay, &shadowHit);
      
        bool inShadow = (shadowHit.matID != -1);
      
        double lightIntensity = dotProduct( &globdat->sun.d , &intersection.normal );
        if (inShadow) {
          lightIntensity = 0.0;
        }

        col = getColor(lightIntensity, &globdat->materials.mat[intersection.matID]);
      }

        Color getCol = getColor( intensity , &globdat->materials.mat[intersection.matID] );
        col.red += getCol.red;
        col.green += getCol.green;
        col.blue += getCol.blue;

      }
    }
      col.red /= globdat->cam.samples_per_pixel;
      col.green /= globdat->cam.samples_per_pixel;
      col.blue /= globdat->cam.samples_per_pixel;

      storePixelRGB( globdat->film , ix , iy , &col );
    }
  }

  free(bvh);
}

//------------------------------------------------------------------------------
//  mapRayToBGCoordinates: Maps the ray direction to the background image
//                         coordinates
//------------------------------------------------------------------------------

void mapRayToBGCoordinates(int* jx, int* jy, Ray ray, Globdat* globdat)
{
  double x = ray.d.x;
  double y = ray.d.y;
  double z = ray.d.z;
 
  double theta = acos(z / ( sqrt(x*x + y*y + z*z)));

  double phi   = atan2(y, x);

  int ny = globdat->bgimage.height;
  int nx = globdat->bgimage.width;

  *jy = (int)(ny * (theta) / PI);
  *jx = (int)(nx * (PI - phi) / (2*PI));
}
