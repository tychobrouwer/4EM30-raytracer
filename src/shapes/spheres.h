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
//  Declaration of the Sphere type (a sphere)
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       centre;
  double     radius;
  int        matID;
} Sphere;


//------------------------------------------------------------------------------
//  Declaration of the Spheres type (a collection of spheres)
//------------------------------------------------------------------------------


typedef struct
{
  Sphere     sphere[MAX_SPHERES];
  int        count;
} Spheres;


//------------------------------------------------------------------------------
//  readSphereData: Reads the sphere data from a file
//
//  Arguments:
//      fin     : File pointer to the file that contains the sphere data
//      spheres : Pointer to the spheres
//
//------------------------------------------------------------------------------


void readSphereData

  ( FILE*        fin     ,
    Spheres*     spheres );

//------------------------------------------------------------------------------
//  addSphere: Adds a sphere to the collection of spheres using the given
//             centre, radius and material ID
//
//  Arguments:
//      spheres : Pointer to the spheres
//      centre  : Centre of the sphere
//      radius  : Radius of the sphere
//      matID   : Material ID of the sphere
//
//  Return:
//      int     : The number of spheres
//
//------------------------------------------------------------------------------


int addSphere

  ( Spheres*     spheres ,
    Vec3         centre  ,
    double       radius  ,
    int          matID   );


//------------------------------------------------------------------------------
//  calcSphereIntersection: Calculates the intersection of a ray with a sphere
//
//  Arguments:
//      intersect : Pointer to the intersection
//      ray       : Pointer to the ray
//      sphere    : Pointer to the sphere
//
//  Return:
//      bool      : True if the ray intersects the sphere, false otherwise
//------------------------------------------------------------------------------


bool calcSphereIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Sphere*       sphere    );
    

#endif


