/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  12/02/2023 | J.Remmers    | Cleaning up code
 *----------------------------------------------------------------------------*/

#ifndef SHAPES_SPHERES_H
#define SHAPES_SPHERES_H

#include <stdbool.h>
#include <stdio.h>
#include "../util/vector.h"
#include "../util/ray.h"

#define MAX_SPHERES 10


//------------------------------------------------------------------------------
//  TODO: COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       centre;
  double     radius;
  int        matID;
} Sphere;


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


typedef struct
{
  Sphere     sphere[MAX_SPHERES];
  int        count;
} Spheres;


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void readSphereData

  ( FILE*        fin     ,
    Spheres*     spheres );

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


int addSphere

  ( Spheres*     spheres ,
    Vec3         centre  ,
    double       radius  ,
    int          matID   );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


bool calcSphereIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Sphere*       sphere    );
    

#endif


