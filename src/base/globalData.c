/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *----------------------------------------------------------------------------*/

#include "globalData.h"

//------------------------------------------------------------------------------
//  initData
//------------------------------------------------------------------------------

void initData

  ( Globdat *globdat )

{
  globdat->mesh.vertexCount   = 0;
  globdat->mesh.faceCount     = 0;
  
  globdat->spheres.count      = 0;

  globdat->sun.intensity      = 0.;
  
  globdat->bgimage.loadedFlag = 0;
}

