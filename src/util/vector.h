/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 * (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *             |              |
 *----------------------------------------------------------------------------*/

#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H

#include <stdbool.h>
#include <math.h>


//------------------------------------------------------------------------------
//  Declaration of the Vec3 type (a vector in three dimensions)
//------------------------------------------------------------------------------

typedef struct 
{
  double     x,y,z;
} Vec3;


//------------------------------------------------------------------------------
//  unit: Calculates the unit of a vector v
//  
//  Arguments:   
//      v      : Vector v, must contain at least 1 non-zero argument. This vector 
//               is normalised (i.e. ||v|| == 1)
//  Return: 
//      float  : The original length of vector  v (float)
//------------------------------------------------------------------------------

double unit

  ( Vec3*   v );


//------------------------------------------------------------------------------
//  length: Calculates the length of vector v
//  
//  Arguments:   
//      v      : Vector v (Vec3)
//
//  Return: 
//     double : The length of vector v, i.e. ||v||
//------------------------------------------------------------------------------

double length

  ( Vec3*    v );


//------------------------------------------------------------------------------
//  dotProduct: Calculates the dotProduct of vectors a and b
//
//  Arguments: 
//      a     : vector a (Vec3)
//      b     : vector b (Vec3)
//
//  Return:  
//      double: The dot product of vectors a and b, i.e. returns a.b
//------------------------------------------------------------------------------

double dotProduct

  ( Vec3*    a ,
    Vec3*    b );


//------------------------------------------------------------------------------
//  crossProduct: Calculates the cross (vector) Product of vectors a and b
//
//  Arguments:
//      a     : vector a (Vec3)
//      b     : vector b (Vec3)
//      c     : vector c (Vec3), which contains the cross product:  c = a x b
//
//  Return:  
//      -
//------------------------------------------------------------------------------

void crossProduct

  ( Vec3*    c ,
    Vec3*    a ,
    Vec3*    b );


//------------------------------------------------------------------------------
//  multiplyVector: Multiplies a vector with a scalar
//
//  Arguments:
//      factor : factor / scalar by which the vector is multiplied
//      v      : vector a (Vec3)
//
//  Return:
//      Vec3   : a vector which is equal to factor * v.
//------------------------------------------------------------------------------

Vec3 multiplyVector

  ( double   factor ,
    Vec3*    v      );


//------------------------------------------------------------------------------
//  addVector: Adds two vectors, each multiplied by a factor
//
//  Arguments:
//      fa      : factor / scalar (double)
//      a       : vector a (Vec3)
//      fb      : factor / scalar (double)
//      b       : vector b (Vec3)
//
//  Return: 
//      Vec3    : A vector that is equal to fa * a + fb * b.
//------------------------------------------------------------------------------

Vec3 addVector

  ( double  fa ,
    Vec3*   a  ,
    double  fb ,
    Vec3*   b  );


//------------------------------------------------------------------------------
//  subtractVector: Subtracts two vectors, each multiplied by a factor
//
//  Arguments:
//      fa      : factor / scalar (double)
//      a       : vector a (Vec3)
//      fb      : factor / scalar (double)
//      b       : vector b (Vec3)
//
//  Return:
//      Vec3    : A vector that is equal to fa * a - fb * b.
//------------------------------------------------------------------------------

Vec3 subtractVector

  ( double  fa ,
    Vec3*   a  ,
    double  fb ,
    Vec3*   b  );

//------------------------------------------------------------------------------
//  minVector: Returns the minimum of two vectors
//
//  Arguments:
//      fa      : factor / scalar (double)
//      a       : vector a (Vec3)
//      fb      : factor / scalar (double)
//      b       : vector b (Vec3)
//
//  Return:
//      Vec3    : A vector that is equal to the minimum of a and b.
//------------------------------------------------------------------------------

Vec3 minVector

  ( double  fa ,
    Vec3*   a  ,
    double  fb ,
    Vec3*   b  );


//------------------------------------------------------------------------------
//  maxVector: Returns the maximum of two vectors
//
//  Arguments:
//      fa      : factor / scalar (double)
//      a       : vector a (Vec3)
//      fb      : factor / scalar (double)
//      b       : vector b (Vec3)
//
//  Return:
//      Vec3    : A vector that is equal to the maximum of a and b.
//------------------------------------------------------------------------------


Vec3 maxVector

  ( double  fa ,
    Vec3*   a ,
    double  fb ,
    Vec3*   b );


//------------------------------------------------------------------------------
//  maxDimension: Returns the dimension in which the vector has an
//                absolute maximum value.
//
//  Arguments:
//      a       : vector a (Vec3)
//
//  Return: 
//      int     : the index (0,1 or 2) of the direction (x,y or z) in which 
//                vector a has the highest value.
//------------------------------------------------------------------------------

int maxDimension

  ( Vec3*   a );


//------------------------------------------------------------------------------
//  permute: Permutes a vector
//
//  Arguments:
//      a       : vector a (Vec3)
//      kx      : unique integer from the collection {0,1,2}
//      ky      : unique integer from the collection {0,1,2}
//      kz      : unique integer from the collection {0,1,2}
//                kx, ky and kz should have different values
//  
//  Return: 
//      Vec3    : Returns a vector b in which a.x is moved to the kx position, a.y 
//                moved to the ky position and a.z moved to the kz position.
//------------------------------------------------------------------------------

Vec3 permute

  ( Vec3   a  ,
    int    kx ,
    int    ky , 
    int    kz );
    
#endif


