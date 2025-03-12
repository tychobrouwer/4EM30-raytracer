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
#include <math.h>
#include <string.h>
#include "film.h"

const int bytesPerPixel = 3; 
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;

const char *RESOLUTION = "Resolution";

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


Film *readFilmData

  ( FILE*       fin )

{
  int height = 0;
  int width  = 0;

  char label[20] = "None";

  fscanf( fin , "%s" , label );

  while( strcmp( label , "End" ) != 0 )
  {
    if( strcmp( label , RESOLUTION ) == 0 )
    {
      fscanf( fin , "%d %d" , &height , &width );
    }

    fscanf( fin , "%s" , label );
  }

  printf("  FILM\n");
  printf("    Size .................... : %d x %d pixels\n",height,width);
  printf("\n");  
  
  return createFilm( height , width );
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

Film *createFilm

  ( int     height , 
    int     width  )

{
  int iPix;
  
  Film *film = (Film*)malloc( height*width*sizeof(Pixel));

  film -> height = height;
  film -> width  = width;

  const int nPix = height*width;

  for ( iPix = 0 ; iPix < nPix ; iPix++ )
  {
    film->p[iPix].c.red   = 0.0;
    film->p[iPix].c.green = 0.0;
    film->p[iPix].c.blue  = 0.0;
    film->p[iPix].wght    = 0.0;
  }
  
  return film;
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void storePixelRGB
  
  ( Film*   film  ,
    int     i     , 
    int     j     ,
    Color*  color )

{
  const int w = film->width;

  film->p[(j*w+i)].c.red   += (float)(color->red);
  film->p[(j*w+i)].c.green += (float)(color->green); 
  film->p[(j*w+i)].c.blue  += (float)(color->blue);

  film->p[(j*w+i)].wght    += 1.0;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

void saveToBitmap

  ( Film* film          , 
    char* imageFileName )

{
  BMPFile *bmpfile = (BMPFile*)malloc( film->height*film->width*3*sizeof(float));
  bmpfile->filename = imageFileName;

  unsigned char padding[3] = {0, 0, 0};
  int paddingSize = (4 - (film->width*bytesPerPixel) % 4) % 4;

  unsigned char* fileHeader = createBitmapFileHeader(film->height, film->width, paddingSize);
  unsigned char* infoHeader = createBitmapInfoHeader(film->height, film->width);

  FILE* imageFile = fopen(imageFileName, "wb");

  fwrite(fileHeader, 1, fileHeaderSize, imageFile);
  fwrite(infoHeader, 1, infoHeaderSize, imageFile);

  int i;

  const int nPix = film->height*film->width;

  float factor;

  for ( i = 0 ; i < nPix ; i++ )
  {
    if ( film->p[i].wght < 1.0e-3 )
    {
      factor = 0.0;
    }
    else
    {
      factor = 1.0/(255.0*film->p[i].wght);
    }
	
    bmpfile->data[3*i+2] = (unsigned char)(sqrt(film->p[i].c.red   * factor) * 255.0);
    bmpfile->data[3*i+1] = (unsigned char)(sqrt(film->p[i].c.green * factor) * 255.0);
    bmpfile->data[3*i+0] = (unsigned char)(sqrt(film->p[i].c.blue  * factor) * 255.0);
  }
 
  for( i=0; i<film->height; i++)
  {
    fwrite((bmpfile->data+(i*film->width*bytesPerPixel)), bytesPerPixel, film->width, imageFile);
    fwrite(padding, 1, paddingSize, imageFile);
  }
  
  fclose(imageFile);
  
  free( film );
  free( bmpfile );
}


//------------------------------------------------------------------------------
//  createBitmapFileHeader
//------------------------------------------------------------------------------


unsigned char* createBitmapFileHeader

   (int      height, 
    int      width, 
    int      paddingSize)

{
  int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel*width+paddingSize) * height;

  static unsigned char fileHeader[] = {
        0,0, /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

  fileHeader[ 0] = (unsigned char)('B');
  fileHeader[ 1] = (unsigned char)('M');
  fileHeader[ 2] = (unsigned char)(fileSize    );
  fileHeader[ 3] = (unsigned char)(fileSize>> 8);
  fileHeader[ 4] = (unsigned char)(fileSize>>16);
  fileHeader[ 5] = (unsigned char)(fileSize>>24);
  fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

  return fileHeader;
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


unsigned char* createBitmapInfoHeader

  (int     height , 
   int     width  )

{
  static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0, /// number of color planes
        0,0, /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

  infoHeader[ 0] = (unsigned char)(infoHeaderSize);
  infoHeader[ 4] = (unsigned char)(width    );
  infoHeader[ 5] = (unsigned char)(width>> 8);
  infoHeader[ 6] = (unsigned char)(width>>16);
  infoHeader[ 7] = (unsigned char)(width>>24);
  infoHeader[ 8] = (unsigned char)(height    );
  infoHeader[ 9] = (unsigned char)(height>> 8);
  infoHeader[10] = (unsigned char)(height>>16);
  infoHeader[11] = (unsigned char)(height>>24);
  infoHeader[12] = (unsigned char)(1);
  infoHeader[14] = (unsigned char)(bytesPerPixel*8);

  return infoHeader;
}
