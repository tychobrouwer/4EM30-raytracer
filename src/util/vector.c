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

#include "vector.h"
#include <math.h>


//------------------------------------------------------------------------------
//  unit: Calculates the unit of a vector v
//------------------------------------------------------------------------------


inline double unit

  ( Vec3*  v )

{
  double l = length(v);
  double invlength = 1.0/l;

  v->x = v->x * invlength;
  v->y = v->y * invlength;
  v->z = v->z * invlength;

  return l;
}


//------------------------------------------------------------------------------
//  length: Calculates the length of vector v
//------------------------------------------------------------------------------


inline double length

  ( Vec3*  v )

{
  return sqrt( dotProduct( v , v ) );
}
 

//------------------------------------------------------------------------------
//  dotProduct: Calculates the dotProduct of vectors a and b
//------------------------------------------------------------------------------


inline double dotProduct

  ( Vec3*  a ,
    Vec3*  b )

{
  return a->x*b->x + a->y*b->y + a->z*b->z;
} 


//------------------------------------------------------------------------------
//  crossProduct: Calculates the cross (vector) Product of vectors a and b
//------------------------------------------------------------------------------


inline void crossProduct

  ( Vec3*    c ,
    Vec3*    a ,
    Vec3*    b )

{
  c->x = a->y*b->z - a->z*b->y;
  c->y = a->z*b->x - a->x*b->z;
  c->z = a->x*b->y - a->y*b->x;
}


//------------------------------------------------------------------------------
//  multiplyVector: Multiplies a vector with a scalar
//------------------------------------------------------------------------------


inline Vec3 multiplyVector

  ( double   factor ,
    Vec3*    v      )

{
  Vec3 output;

  output.x = factor * v->x;
  output.y = factor * v->y;
  output.z = factor * v->z;

  return output;
}


//------------------------------------------------------------------------------
//  addVector: Adds two vectors, each multiplied by a factor
//------------------------------------------------------------------------------


inline Vec3 addVector

  ( double  fa ,
    Vec3*   a  ,
    double  fb ,
    Vec3*   b  )

{
  Vec3 c;

  c.x = fa * a->x + fb * b->x;
  c.y = fa * a->y + fb * b->y;
  c.z = fa * a->z + fb * b->z;

  return c;
}

//------------------------------------------------------------------------------
//  minVector: Returns the minimum of two vectors, each multiplied by a factor
//------------------------------------------------------------------------------


inline Vec3 minVector

  ( double  fa ,
    Vec3*   a  ,
    double  fb ,
    Vec3*   b  )
{
  Vec3 c;
  c.x = a->x < b->x ? a->x : b->x;
  c.y = a->y < b->y ? a->y : b->y;
  c.z = a->z < b->z ? a->z : b->z;
  return c;
}


//------------------------------------------------------------------------------
//  maxVector: Returns the maximum of two vectors, each multiplied by a factor
//------------------------------------------------------------------------------


inline Vec3 maxVector

  ( double fa ,
    Vec3*  a  ,
    double fb ,
    Vec3*  b  )
{
  Vec3 c;
  c.x = a->x > b->x ? a->x : b->x;
  c.y = a->y > b->y ? a->y : b->y;
  c.z = a->z > b->z ? a->z : b->z;
  return c;
}


//------------------------------------------------------------------------------
//  maxDimension: Returns the dimension in which the vector has an
//                absolute maximum value.
//------------------------------------------------------------------------------


inline int maxDimension

  ( Vec3*   a )

{
  if( fabs(a->x) > fabs(a->y) && fabs(a->x) > fabs(a->z) )
  {
    return 0;
  }
  else if (fabs(a->y) > fabs(a->z) )
  {
    return 1;
  }
  else
  {
    return 2;
  }
}

//------------------------------------------------------------------------------
//  permute: Permutes a vector
//------------------------------------------------------------------------------

inline Vec3 permute

  ( Vec3   a  ,
    int    kx ,
    int    ky , 
    int    kz )

{
  const double* vals = &a.x;
  return (Vec3){vals[kx], vals[ky], vals[kz]};
}
