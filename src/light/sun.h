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
//  COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       d;
  double     intensity;
} Sun;


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void readSunData

  ( FILE*      fin ,
    Sun*       sun );

#endif
