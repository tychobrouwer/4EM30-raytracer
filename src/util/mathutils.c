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

#include "mathutils.h"
#include <math.h>

bool quadratic

  ( double     a    ,
    double     b    , 
    double     c    , 
    double*    t0   ,
    double*    t1   )

{
  double discr = b*b-4.*a*c;

  if( discr < 0.0 )
  {
    return false;
  }
  else
  {
    discr = sqrt(discr);

    *t0 = ( -b - discr ) / (2.0*a);
    *t1 = ( -b + discr ) / (2.0*a);
  }
 
  return true;
}



