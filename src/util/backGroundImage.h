/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  01/01/2024 | J.Remmers    | First version
 *----------------------------------------------------------------------------*/

#ifndef UTIL_BACKGROUNDIMAGE_H
#define UTIL_BACKGROUNDIMAGE_H

#include <stdio.h>
#include "color.h"


//------------------------------------------------------------------------------
//  COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


typedef struct
{
  char            filename[40];
  int             width;
  int             height;
  int             channels;
  int             hdrFlag;
  int             loadedFlag;
  unsigned char   *data;
  float           *hdrdata;
} BGImage;


//------------------------------------------------------------------------------
//  
//------------------------------------------------------------------------------


void readBackGroundImage

  ( FILE*         in       ,
    BGImage       *bgimage );


//------------------------------------------------------------------------------
//  
//------------------------------------------------------------------------------


void createBackGroundImage

  ( char*    name    ,
    BGImage *bgimage );
  
  
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

  
Color getBGImagePixelValue

  ( BGImage *im2 ,
    int      x   ,
    int      y   );
    

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

  
void freeBGImage

  ( BGImage *im2 );
    
        
#endif
