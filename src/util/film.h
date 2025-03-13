/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  12/02/2023 | J.Remmers    | Cleaning up code
 *----------------------------------------------------------------------------*/

#ifndef UTIL_FILM_H
#define UTIL_FILM_H

#include <stdio.h>
#include "color.h"

//------------------------------------------------------------------------------
//  Declaration of the BMPFile type (a bitmap file)
//------------------------------------------------------------------------------


typedef struct
{
  char*           filename;
  unsigned char   data[];
} BMPFile;


//------------------------------------------------------------------------------
//  Declaration of the Pixel type (a pixel in the film)
//------------------------------------------------------------------------------


typedef struct
{
  Color           c;
  float           wght;
} Pixel;


//------------------------------------------------------------------------------
//  Declaration of the Film type (a film)
//------------------------------------------------------------------------------


typedef struct
{
  int             height;
  int             width;
  Pixel           p[];
} Film;


//------------------------------------------------------------------------------
//  readFilmData: Reads the film data from a file
//
//  Arguments:
//      in      : File pointer to the file that contains the film data
//
//  Return:
//      Film*   : a pointer to the film
//
//------------------------------------------------------------------------------


Film *readFilmData

  ( FILE*         in );


//------------------------------------------------------------------------------
//  createFilm: Creates a film with a given height and width
//
//  Arguments:
//      height  : height of the film
//      width   : width of the film
//
//  Return:
//      Film*   : a pointer to the film
//
//------------------------------------------------------------------------------


Film *createFilm 

  ( int           height , 
    int           width  );


//------------------------------------------------------------------------------
//  storePixelRGB: Stores a pixel in the film
//
//  Arguments:
//      film    : Film in which the pixel is stored
//      i       : row index of the pixel
//      j       : column index of the pixel
//      color   : color of the pixel
//
//------------------------------------------------------------------------------


void storePixelRGB
  
  ( Film*         film  ,
    int           i     , 
    int           j     ,
    Color*        color );


//------------------------------------------------------------------------------
//  createBitmapFileHeader: Creates the bitmap file header
//
//  Arguments:
//      height      : height of the bitmap
//      width       : width of the bitmap
//      paddingSize : size of the padding
//
//  Return:
//      unsigned char* : a pointer to the bitmap file header
//
//------------------------------------------------------------------------------


unsigned char* createBitmapFileHeader

  ( int           height     , 
    int           width      , 
    int           paddingSize);


//------------------------------------------------------------------------------
//  createBitmapInfoHeader: Creates the bitmap info header
//
//  Arguments:
//      height  : height of the bitmap
//      width   : width of the bitmap
//
//  Return:
//      unsigned char* : a pointer to the bitmap info header
//
//------------------------------------------------------------------------------


unsigned char* createBitmapInfoHeader

  ( int           height , 
    int           width  );


//------------------------------------------------------------------------------
//  saveToBitmap: Saves the film to a bitmap file
//
//  Arguments:
//      film          : Film that is saved to the bitmap file
//      imageFileName : Name of the bitmap file
//
//------------------------------------------------------------------------------


void saveToBitmap

  ( Film*         film          , 
    char*         imageFileName );

#endif
