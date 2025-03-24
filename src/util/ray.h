/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  12/02/2023 | J.Remmers    | Adding specific instructions for students 
 *----------------------------------------------------------------------------*/

#ifndef UTILS_RAYS_H
#define UTILS_RAYS_H

#include "vector.h"


//------------------------------------------------------------------------------
//  Intersect:  structure to store the properties of an intersection
//      t       : Distance of intersection from origin of the ray.
//      normal  : Normal of intersected surface
//      matID   : material ID of intersected surface
//------------------------------------------------------------------------------


typedef struct 
{
  double      t;
  Vec3        normal;
  int         matID;
} Intersect;


//------------------------------------------------------------------------------
//  Ray:   structure to store the propoperties of a ray
//      o      : origin (Vec3)
//      d      : direction (Vec3)
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3        o;
  Vec3        d;
} Ray;


//------------------------------------------------------------------------------
//  resetIntersect: function to resect the values of the intersection variable.
//  It sets the distance of the intersection to infinity and the materialID to -1.
//  
//  Arguments:
//     intersect : properties of the intersection
//------------------------------------------------------------------------------


void resetIntersect

  ( Intersect*  intersect );
  
#endif


