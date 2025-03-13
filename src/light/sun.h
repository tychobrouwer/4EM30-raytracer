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

#ifndef LIGHT_SUN_H
#define LIGHT_SUN_H

#include <stdbool.h>
#include "../util/vector.h"

//------------------------------------------------------------------------------
//  Declaration of the Sun type (a sun)
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       d;
  double     intensity;
} Sun;


//------------------------------------------------------------------------------
//  readSunData: Reads the sun data from a file
//
//  Arguments:
//      fin     : File pointer to the file that contains the sun data
//      sun     : Pointer to the sun
//
//------------------------------------------------------------------------------


void readSunData

  ( FILE*      fin ,
    Sun*       sun );

#endif
