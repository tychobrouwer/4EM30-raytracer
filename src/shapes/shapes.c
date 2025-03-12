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

#include "shapes.h"

//------------------------------------------------------------------------------
//  calcIntersection
//------------------------------------------------------------------------------


void calcIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Globdat*      globdat   )

{
  int iShp;
  
  for ( iShp = 0 ; iShp < globdat->spheres.count ; iShp++ )
  {
    calcSphereIntersection( intersect , ray , &globdat->spheres.sphere[iShp] );
  }

  Face face;

  for ( iShp = 0 ; iShp < globdat->mesh.faceCount ; iShp++ )
  {
    getFace( &face , iShp , &globdat->mesh );

    calcFaceIntersection( intersect , ray , &face );
  }
}
