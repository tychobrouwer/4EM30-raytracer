/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *             |              |
 *----------------------------------------------------------------------------*/

#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H

#include <stdbool.h>
#include "../util/vector.h"
#include "../util/ray.h"
#include "../util/film.h"

//------------------------------------------------------------------------------
//  COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       origin;
  double     fov;
  double     y0,z0,dx;
} CameraData;


//
//
//


void readCameraData

  ( FILE*       fin ,
    CameraData* cam );

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void initialiseCamera
 
  ( CameraData*  cam  ,
    Film*        film );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void generateRay

  ( Ray*          ray ,
    int           ix  ,
    int           iy  ,
    CameraData*   cam );
  
#endif


