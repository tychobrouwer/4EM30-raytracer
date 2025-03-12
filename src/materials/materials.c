/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2023 | J.Remmers    | First version
 *             |              |
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "materials.h"
#include "../util/mathutils.h"


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void readMaterialData

  ( FILE*       fin       ,
    Materials*  materials )

{
  // Add code to read material data below.
  //
  //
  
  // Remove the part below as it contains hard code material property data to
  // trace the sample images
  
  // Assign 4 different shades of gray to all material IDs
  
  int    iMat;
  double c;
  
  for ( int iMat = 0 ; iMat < MAX_MATERIALS ; iMat++ )
  {
    double c = 100.0 + 30.*(iMat%4);
        
    materials->mat[iMat].type        = 0;
    materials->mat[iMat].base.red    = c;
    materials->mat[iMat].base.green  = c;
    materials->mat[iMat].base.blue   = c;
  }
  
  // Assign specific colors for the single pin and the BMW cases
      
  
  materials->mat[0].type        = 0;
  materials->mat[0].base.red    = 5.;
  materials->mat[0].base.green  = 5.;
  materials->mat[0].base.blue   = 5.;
  
  materials->mat[1].type        = 0;
  materials->mat[1].base.red    = 255.;
  materials->mat[1].base.green  = 0.;
  materials->mat[1].base.blue   = 0.;

  materials->mat[2].type        = 0;
  materials->mat[2].base.red    = 5.;
  materials->mat[2].base.green  = 155.;
  materials->mat[2].base.blue   = 0.;
  
  materials->mat[4].type        = 0;
  materials->mat[4].base.red    = 255.;
  materials->mat[4].base.green  = 255.;
  materials->mat[4].base.blue   = 0.;
  
  materials->mat[16].type        = 0;
  materials->mat[16].base.red    = 0.;
  materials->mat[16].base.green  = 0.;
  materials->mat[16].base.blue   = 230.;
  
  materials->mat[22].type        = 0;
  materials->mat[22].base.red    = 20.;
  materials->mat[22].base.green  = 20.;
  materials->mat[22].base.blue   = 20.;

  materials->mat[23].type        = 0;
  materials->mat[23].base.red    = 0.;
  materials->mat[23].base.green  = 154.;
  materials->mat[23].base.blue   = 201.;
  
  materials->mat[24].type        = 0;
  materials->mat[24].base.red    = 184.;
  materials->mat[24].base.green  = 202.;
  materials->mat[24].base.blue   = 209.;
  
  materials->mat[25].type        = 0;
  materials->mat[25].base.red    = 250.;
  materials->mat[25].base.green  = 250.;
  materials->mat[25].base.blue   = 250.;        
}


//
//
//


Color getColor

  ( double        intensity ,
    Material*     material  )
    
{
  Color col;
    
  col.red   = intensity * material->base.red;
  col.green = intensity * material->base.green;
  col.blue  = intensity * material->base.blue;    

  return col;
}
