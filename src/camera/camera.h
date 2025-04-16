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
//  Declaration of the CameraData type (a camera)
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       origin,tilt;
  double     fov;
  int        samples_per_pixel;
  bool       strat;
  double     u,v;
  double     y0,z0,dx;
} CameraData;


//------------------------------------------------------------------------------
//  readCameraData: Reads the camera data from a file
//
//  Arguments:
//      fin     : File pointer to the file that contains the camera data
//      cam     : Pointer to the camera
//
//------------------------------------------------------------------------------


void readCameraData

  ( FILE*       fin ,
    CameraData* cam );

//------------------------------------------------------------------------------
//  initialiseCamera: Initialises the camera object
//
//  Arguments:
//      cam     : Pointer to the camera
//      film    : Pointer to the film
//
//------------------------------------------------------------------------------


void initialiseCamera
 
  ( CameraData*  cam  ,
    Film*        film );


//------------------------------------------------------------------------------
//  generateRay: Generates a ray for a given pixel
//
//  Arguments:
//      ray     : Pointer to the ray
//      ix      : x-coordinate of the pixel
//      iy      : y-coordinate of the pixel
//      cam     : Pointer to the camera
//
//------------------------------------------------------------------------------


void generateRay

  ( Ray*          ray ,
    int           ix  ,
    int           iy  ,
    double        u   ,
    double        v   ,
    CameraData*   cam );

#endif


