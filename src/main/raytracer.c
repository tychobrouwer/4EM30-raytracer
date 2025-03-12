/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  21/02/2021 | J.Remmers    | Assigned a specific length to fileName
 *  12/02/2023 | J.Remmers    | Cleaning up the code
 *             |              |
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "../base/globalData.h"
#include "../base/readInput.h"
#include "../base/preprocess.h"
#include "../base/trace.h"
#include "../base/shutdown.h"

int main( int argc, char *argv[] )  

{  
  Globdat globdat;

  initData( &globdat );

  if (argc == 0 || argc == 1 )  
  { 
    printf("Please rerun the executable with the correct input filename\n");
    printf("For example:   raytracer.exe singlePin.in\n"); 
    return 0; 
  }
     
  readInput ( argv[1] , &globdat );
  preprocess( &globdat );
  
  trace     ( &globdat );

  shutdown  ( &globdat );

  return 0;
}
