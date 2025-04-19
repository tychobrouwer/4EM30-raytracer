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

#include "globalData.h"
#include "../util/bvh.h"


//------------------------------------------------------------------------------
//  trace: Traces the rays through the scene
//
//  Arguments:
//      globdat : Pointer to the global data
//
//------------------------------------------------------------------------------

void trace

  ( Globdat*  globdat );


//------------------------------------------------------------------------------
//  computeIntensity: Computes the intensity of a pixel from the shadows
//
//  Arguments:
//      globdat      : Pointer to the global data
//      bvh          : Pointer to the bvh data structure
//      ray          : Ray structure
//      intersection : Intersection point of the ray with the scene
//
//------------------------------------------------------------------------------


double computeIntensity

  ( Globdat* globdat,
    BVH *bvh,
    Vec3 *offsets,
    Ray *ray,
    Intersect *intersection );


//------------------------------------------------------------------------------
//  mapRayToBGCoordinates: Maps the ray direction to the background image
//                         coordinates
//
//  Arguments:
//      jx      : Pointer to the x-coordinate in the background image
//      jy      : Pointer to the y-coordinate in the background image
//      ray     : Ray structure
//      globdat : Pointer to the global data
//
//------------------------------------------------------------------------------


void mapRayToBGCoordinates

  ( int* jx,
    int* jy,
    Ray ray,
    Globdat* globdat );

#endif
