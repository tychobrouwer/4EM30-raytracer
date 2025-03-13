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
//  Declaration of the BGImage type (a background image)
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
//  readBackGroundImage: Reads the background image from a file
//
//  Arguments:
//      in      : File pointer to the file that contains the background image
//      bgimage : Pointer to the background image
//
//------------------------------------------------------------------------------


void readBackGroundImage

  ( FILE*         in       ,
    BGImage       *bgimage );


//------------------------------------------------------------------------------
//  createBackGroundImage: Creates the background image
//
//  Arguments:
//      name    : Name of the background image
//      bgimage : Pointer to the background image
//
//------------------------------------------------------------------------------


void createBackGroundImage

  ( char*    name    ,
    BGImage *bgimage );
  
  
//------------------------------------------------------------------------------
//  getBGImagePixelValue: Returns the pixel value of the background image
//
//  Arguments:
//      im2     : Pointer to the background image
//      x       : x-coordinate of the pixel
//      y       : y-coordinate of the pixel
//
//  Return:
//      Color   : The color of the pixel
//
//------------------------------------------------------------------------------

  
Color getBGImagePixelValue

  ( BGImage *im2 ,
    int      x   ,
    int      y   );
    

//------------------------------------------------------------------------------
//  freeBGImage: Frees the memory of the background image
//
//  Arguments:
//      im2     : Pointer to the background image
//
//------------------------------------------------------------------------------

  
void freeBGImage

  ( BGImage *im2 );
    
        
#endif
