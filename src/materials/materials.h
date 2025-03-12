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

#ifndef MATERIALS_MATERIALS_H
#define MATERIALS_MATERIALS_H

#include <stdbool.h>
#include "../util/color.h"

#define MAX_MATERIALS 100


//------------------------------------------------------------------------------
//  COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


typedef struct 
{
  int        type;
  Color      base;
} Material;


typedef struct
{
  Material   mat[MAX_MATERIALS];
} Materials;


//
//
//


void readMaterialData

  ( FILE*       fin       ,
    Materials*  materials );


Color getColor

  ( double        intensity ,
    Material*     material  );
    
#endif


