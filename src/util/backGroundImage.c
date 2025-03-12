/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  05/01/2024 | J.Remmers    | First version
 *             |              |
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "backGroundImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *IMAGE = "Image";

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void readBackGroundImage

  ( FILE*         fin     ,
    BGImage*      bgimage )

{
  int height = 0;
  int width  = 0;

  char label[20] = "None";
  
  char imageName[40] = "None";

  fscanf( fin , "%s" , label );

  while( strcmp( label , "End" ) != 0 )
  {
    if( strcmp( label , IMAGE ) == 0 )
    {
      fscanf( fin , "%s" , bgimage->filename );
    }

    fscanf( fin , "%s" , label );
  }
    
  createBackGroundImage( imageName , bgimage );
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

void createBackGroundImage

  ( char*      filename ,
    BGImage*   bgimage  )

{
  int width,height,channels;
  
  bgimage->loadedFlag = 1;
    
  bgimage->hdrFlag  = stbi_is_hdr( bgimage->filename );
  
  printf("\n  BACKGROUND IMAGE \n" ); 
  printf("    Filename ................ : %s \n",bgimage->filename );  
  
  if ( bgimage->hdrFlag )
  {
    float* image = stbi_loadf( bgimage->filename , 
                               &width, &height, &channels, 0);  

    if ( image != NULL) 
    {
      bgimage->loadedFlag = 1;
    }
        
    bgimage->hdrdata = image;
  }
  else
  {
    unsigned char* image = stbi_load( bgimage->filename , 
                                      &width, &height, &channels, 0);
      
    if ( image != NULL) 
    {
      bgimage->loadedFlag = 1;
    }    

    bgimage->data = image;    
  }
  
  if ( bgimage->loadedFlag ) 
  {
    printf("    Dimensions .............. : %d x %d pixels.\n", width, height);
    printf("    Number of channels ...... : %d\n", channels);
    
    bgimage->width    = width;
    bgimage->height   = height;
    bgimage->channels = channels;                
  } 
  else 
  {
    printf("Failed to load the image: %s\n", stbi_failure_reason());
  }
  
  printf("\n");
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

Color getBGImagePixelValue

  ( BGImage *bgimage ,
    int      x       ,
    int      y       )

{
  Color col;
  
  int pixelIndex = ( x + y * bgimage->width )*3;
  
  if ( bgimage->hdrFlag )
  {
    col.red   = (int)255*bgimage->hdrdata[pixelIndex + 0];
    col.green = (int)255*bgimage->hdrdata[pixelIndex + 1];
    col.blue  = (int)255*bgimage->hdrdata[pixelIndex + 2];
  
    if(col.red > 255 )
    { 
      col.red = 255;
    }
    else if ( col.red < 0 )
    {
      col.red = 0;
    }
  
    if(col.green > 255 )
    {   
      col.green = 255;
    }
    else if ( col.green < 0 )
    {
      col.green = 0;
    }
  
    if(col.blue > 255 )
    { 
      col.blue = 255;
    }
    else if ( col.blue < 0 )
    {
      col.blue = 0;
    }    
  }
  else
  {
    col.red   = (int)255*bgimage->data[pixelIndex + 0];
    col.green = (int)255*bgimage->data[pixelIndex + 1];
    col.blue  = (int)255*bgimage->data[pixelIndex + 2];
  }
      
  return col;
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

  
void freeBGImage

  ( BGImage *bgimage )
  
{
  if ( bgimage->loadedFlag )
  {
    if ( bgimage->hdrFlag )
    {
      stbi_image_free( bgimage->hdrdata );
    }
    else
    {
      stbi_image_free( bgimage->data );  
    }
  }
}
  
  


