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

#ifndef BASE_TRACE_H
#define BASE_TRACE_H

#include <omp.h>

#include "globalData.h"


//------------------------------------------------------------------------------
//  trace: Traces the rays through the scene
//
//  Arguments:
//      globdat : Pointer to the global data
//
//------------------------------------------------------------------------------

void trace

  ( Globdat*  globdat );

#endif


