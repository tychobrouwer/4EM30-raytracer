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

#ifndef BASE_READINPUT_H
#define BASE_READINPUT_H

#include "globalData.h"


//------------------------------------------------------------------------------
//  readInput: Reads the input data from a file
//
//  Arguments:
//      fileName : Name of the file that contains the input data
//      globdat  : Pointer to the global data
//
//------------------------------------------------------------------------------


void readInput

  ( char*     fileName ,
    Globdat*  globdat );

#endif


