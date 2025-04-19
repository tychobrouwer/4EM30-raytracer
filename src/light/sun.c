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

#include <stdio.h>
#include <string.h>
#include "sun.h"

const char* INTENSITY = "Intensity";

//------------------------------------------------------------------------------
//  readSunData: Reads the sun data from a file
//------------------------------------------------------------------------------


void readSunData

  ( FILE*       fin ,
    Sun*        sun )

{
  char label[20] = "None";

  fscanf( fin , "%s" , label );

  while( strcmp( label , "End" ) != 0 )
  {
    if( strcmp( label , "Direction" ) == 0 )
    {
      fscanf( fin , "%le %le %le" , &sun->d.x , &sun->d.y , &sun->d.z );
    }
    else if ( strcmp( label , INTENSITY ) == 0 )
    {
      fscanf( fin , "%le" , &sun->intensity );
    }

    fscanf( fin , "%s" , label );
  }

  unit( &sun->d );

  sun->d = multiplyVector( sun->intensity , &sun->d );

  printf("  SUN\n");
  printf("    Direction ............... : %f %f %f \n\n",sun->d.x,sun->d.y,sun->d.z);
}
