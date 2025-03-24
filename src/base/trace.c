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


//------------------------------------------------------------------------------
//  trace: Traces the rays through the scene
//------------------------------------------------------------------------------


void trace

  ( Globdat*  globdat )

{
  printf("\n  +++ Start tracing +++\n");

  int ix,iy;

  Ray   ray;
  Color col;

  Intersect intersection;

  for ( ix = 0 ; ix < globdat->film->width ; ix++ )
  {
    for ( iy = 0 ; iy < globdat->film->height ; iy++ )
    {
      generateRay( &ray , ix , iy , &globdat->cam );
      
      resetIntersect( &intersection );
      
      calcIntersection( &intersection , &ray , globdat );

      double intensity = dotProduct( &globdat->sun.d , &intersection.normal );

      if (intensity < 0. )
      {
        intensity = 0;
      }
      
      /* All code below this line related to the background image is 'hardcoded' 
      without using and must be changed as part of the project.
      Please make sure that you use abstraction, magic numbers etc.
      Note that a sloppy code as shown below requires a lot of comments.
      Make sure that you do not need comments in your final code.*/
     
      if ( intersection.matID == -1 )
      {
        //printf("TTTT %d\n",globdat->bgimage.loadedFlag);
        
        if ( globdat->bgimage.loadedFlag == 1 )
        {
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
                  
          col = getBGImagePixelValue( &globdat->bgimage , jx , jy );
        }
        else
        {
          col.red   = (int)255*0.678; 
          col.green = (int)255*0.847;
          col.blue  = (int)255*0.902;
        }
      }
      else
      {
        col = getColor( intensity , &globdat->materials.mat[intersection.matID] );
      }
           
      storePixelRGB( globdat->film , ix , iy , &col );
    }
  }
}

