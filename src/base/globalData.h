/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  12/02/2023 | J.Remmers    | Adding materials datastructure
 *----------------------------------------------------------------------------*/

#ifndef BASE_GLOBAL_DATA_H
#define BASE_GLOBAL_DATA_H

#include "../camera/camera.h"
#include "../light/sun.h"
#include "../materials/materials.h"
#include "../shapes/mesh.h"
#include "../shapes/spheres.h"
#include "../util/backGroundImage.h"
#include "../util/film.h"
#include "../util/vector.h"
#include "../light/spotlight.h"



//------------------------------------------------------------------------------
//  Declaration of the Globdat type (a global data structure)
//------------------------------------------------------------------------------


typedef struct 
{
  CameraData  cam;
  Film        *film;
  BGImage     bgimage;
  Materials   materials;
  Spheres     spheres;
  Mesh        mesh;
  
  Sun         sun;
  Spotlights  spotlights;

  char        filename[40];
} Globdat;


//------------------------------------------------------------------------------
//  initData: Initialises the global data
//
//  Arguments:
//      globdat : Pointer to the global data
//
//------------------------------------------------------------------------------


void initData

  ( Globdat *globdat );

#endif


