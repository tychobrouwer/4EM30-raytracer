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

#ifndef BASE_PREPROCESS_H
#define BASE_PREPROCESS_H

#include "globalData.h"

//------------------------------------------------------------------------------
//  preprocess: Preprocesses the data
//
//  Arguments:
//      globdat : Pointer to the global data
//
//------------------------------------------------------------------------------


void preprocess

  ( Globdat   *globdat );



void calcVertexNormal
  ( Mesh*   mesh     );

#endif


