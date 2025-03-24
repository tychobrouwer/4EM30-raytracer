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

#include <stdio.h>
#include "spheres.h"
#include "../util/mathutils.h"

//------------------------------------------------------------------------------
//  readSphereData: Reads the sphere data from a file
//------------------------------------------------------------------------------


void readSphereData

  ( FILE*       fin     ,
    Spheres*    spheres )

{
  int iSph;
  int nSph = 0;

  int    matID;
  Vec3   centre;
  double radius;

  fscanf( fin , "%d" , &nSph );

  for( iSph = 0 ; iSph < nSph ; iSph++ )
  {
    fscanf( fin , "%d %le %le %le %le" , &matID , &centre.x , 
                                         &centre.y , &centre.z , 
                                         &radius );
    
    addSphere( spheres , centre , radius , matID );
  }
 
  printf("    Number of spheres ....... : %d\n",spheres->count);
}


//-----------------------------------------------------------------------------
//  addSphere: Adds a sphere to the collection of spheres using the given
//             centre, radius and material ID
//-----------------------------------------------------------------------------


int addSphere

  ( Spheres*     spheres ,
    Vec3         centre  ,
    double       radius  ,
    int          matID   )

{
  int sphereID = spheres->count;
  
  spheres->sphere[sphereID].centre.x = centre.x;
  spheres->sphere[sphereID].centre.y = centre.y;
  spheres->sphere[sphereID].centre.z = centre.z;

  spheres->sphere[sphereID].radius   = radius;

  spheres->sphere[sphereID].matID    = matID;

  spheres->count++;

  return sphereID;
}


//------------------------------------------------------------------------------
//  calcSphereIntersection: Calculates the intersection of a ray with a sphere
//------------------------------------------------------------------------------


bool calcSphereIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Sphere*       sphere    )

{
  Vec3     relo;  //Relative origin of ray;
  double   a,b,c,t0,t1;
  bool     intersectFlag = false;

  relo = addVector( 1.0 , &ray->o , -1.0 , &sphere->centre );

  a = dotProduct( &ray->d , &ray->d );

  b = 2.0* dotProduct( &ray->d , &relo );

  c = dotProduct( &relo , &relo ) - sphere->radius * sphere->radius;

  if( quadratic( a , b , c , &t0 , &t1 ) )
  {
    if( t0 > 0. )
    {
      if( t0 < intersect->t )
      {
        intersect->t     = t0;
        intersect->matID = sphere->matID;
        intersectFlag    = true;
      }
    }
    else if ( t1 > 0. )
    {
      if( t1 < intersect->t ) 
      {
        intersect->t     = t1;
        intersect->matID = sphere->matID;
        intersectFlag    = true;       
      }
    }

    if ( intersectFlag )
    {
      intersect->normal = addVector( 1.0 , &relo , intersect->t , &ray->d );
     
      unit( &intersect->normal );
    }

    return intersectFlag;
  }
  
  return false;
}    
