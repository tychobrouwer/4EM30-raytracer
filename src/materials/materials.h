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
//  Declaration of the Material type (a material)
//------------------------------------------------------------------------------


typedef struct 
{
  int        type;
  Color      base;
} Material;


//------------------------------------------------------------------------------
//  Declaration of the Materials type (a collection of materials)
//------------------------------------------------------------------------------


typedef struct
{
  Material   mat[MAX_MATERIALS];
} Materials;


//------------------------------------------------------------------------------
//  readMaterialData: Reads the material data from a file
//
//  Arguments:
//      fin       : File pointer to the file that contains the material data
//      materials : Pointer to the materials
//
//------------------------------------------------------------------------------


void readMaterialData

  ( FILE*       fin       ,
    Materials*  materials );


//------------------------------------------------------------------------------
// getColor: Returns the color of a material
//
//  Arguments:
//      intensity : intensity of the color
//      material  : Pointer to the material
//
//  Return:
//      Color     : The color of the material
//
//------------------------------------------------------------------------------


Color getColor

  ( double        intensity ,
    Material*     material  );
    
#endif


