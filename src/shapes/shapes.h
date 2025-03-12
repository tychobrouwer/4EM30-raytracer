/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  03/03/2024 | J.Remmers    | Removed bool from calcIntersection
 *             |              |
 *----------------------------------------------------------------------------*/

#ifndef SHAPES_SHAPES_H
#define SHAPES_SHAPES_H

#include <stdbool.h>
#include "spheres.h"
#include "../base/globalData.h"

//------------------------------------------------------------------------------
//  COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


void calcIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Globdat*      globdat   );
    
#endif


