/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  06/01/2024 | J.Remmers    | Adding freeBAckGroundImage
 *             |              |
 *----------------------------------------------------------------------------*/

#include "shutdown.h"
#include "../shapes/mesh.h"
#include "../util/film.h"
#include "../util/backGroundImage.h"

//------------------------------------------------------------------------------
//  shutdown: Shuts down the RayTracer
//------------------------------------------------------------------------------


void shutdown

  ( Globdat*  globdat )

{
  saveToBitmap( globdat->film , globdat->filename );
  
  freeBGImage( &globdat->bgimage );
  freeMesh   ( &globdat->mesh );  

  printf("\n  The Raytracer has finished successfully.\n");
  printf("  The image is stored in the file '%s'.\n",globdat->filename);
}

