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
#include <stdlib.h>
#include <string.h>

#include "readInput.h"

const char *ENDINPUT  = "EndInput";
const char *CAMERA    = "Camera";
const char *FILM      = "Film";
const char *BACKGROUND= "BackGround";
const char *SUN       = "Sun";
const char *SPHERES   = "Spheres";
const char *FACES     = "Faces";
const char *VERTICES  = "Vertices";
const char *FILENAME  = "Filename";
const char *MATERIALS = "Materials";
const char *SPOTLIGHTS = "Spotlights";

//------------------------------------------------------------------------------
//  readInput: Reads the input data from a file
//------------------------------------------------------------------------------


void readInput

  ( char*     fileName ,
    Globdat*  globdat  )

{
  FILE *fin;

  if ( ( fin=fopen(fileName,"r") ) == NULL) 
  {
    printf("Cannot open file %s. It seems that it does not exist in this directory.\n",
              fileName);
    printf("Please specify a new filename...... : ");
    scanf ("%s" , fileName );
    printf("\n");
    readInput( fileName , globdat );
    return;
  }

  char label[20];

  fscanf( fin, "%s", label );
  
  printf("\n  Input filename .......... : %s\n",fileName);
 
  while( strcmp( label , ENDINPUT ) != 0 )
  {
    if ( strcmp( label , CAMERA ) == 0 )
    {
      readCameraData( fin , &globdat->cam );
    }
    else if ( strcmp( label , FILM ) == 0 )
    {
      globdat->film = readFilmData( fin );
    }
    else if ( strcmp( label , BACKGROUND ) == 0 )
    {
      readBackGroundImage( fin , &globdat->bgimage );
    }    
    else if ( strcmp( label , SUN ) == 0 )
    {
      readSunData( fin , &globdat->sun );
    }
    else if ( strcmp( label , SPOTLIGHTS ) == 0 )
    {
      readSpotlightData( fin , &globdat->spotlights );
    }
    else if ( strcmp( label , SPHERES ) == 0 )
    {
      readSphereData( fin , &globdat->spheres );
    }
    else if ( strcmp( label , FACES ) == 0 )
    {
      readFaceData( fin , &globdat->mesh );
    }
    else if ( strcmp( label , VERTICES ) == 0 )
    {
      readVertexData( fin , &globdat->mesh );
    }
    else if ( strcmp( label , MATERIALS ) == 0 )
    {
      readMaterialData( fin , &globdat->materials );
    }    
    else if( strcmp( label , FILENAME ) == 0 )
    {
      fscanf( fin , "%s" , globdat->filename );
      printf("  Output filename.......... : %s\n\n",globdat->filename);
    }
   
    fscanf( fin, "%s", label );
  }

  printf("\n  +++ Input file read +++\n");
}

