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

#include "ray.h"

//------------------------------------------------------------------------------
//  resetIntersect: function to resect the values of the intersection variable.
//  It sets the distance of the intersection to infinity and the materialID to -1.
//------------------------------------------------------------------------------

void resetIntersect

  ( Intersect*  intersect )

{
  intersect->t     = 1.0e20;
  intersect->matID = -1;
}
 
