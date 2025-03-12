/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  12/02/2023 | J.Remmers    | Adding 16 digit pi and specific instructions.
 *----------------------------------------------------------------------------*/

#ifndef UTIL_MATHUTILS_H
#define UTIL_MATHUTILS_H

#include <stdbool.h>
#include <math.h>

#define PICONST 3.141592653589793


//------------------------------------------------------------------------------
//  Function to solve the solutions of a quadratic equation of the form
//  a*t^2 + b*t + c = 0
//
//  Arguments
//     a       : parameter a (float). Must be non-zero
//     b       : parameter b (float)
//     c       : parameter c (float)
//     t0      : first solution (float, return argument)
//     t1      : second solution (float, return argument, by definition t0<t1)
//
//  Returns
//     bool    : true if one or two solutions are found.
//------------------------------------------------------------------------------


bool quadratic

  ( double          a  ,
    double          b  , 
    double          c  , 
    double*         t0 ,
    double*         t1 );
    

#endif


