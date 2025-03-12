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

#include "../util/vector.h"
#include "../util/film.h"

int main( void )

{
  // Test Vector utilities

  Vec3 a;

  a.x = 3.0;
  a.y = 4.0;
  a.z = 0.0;

  double l = length( &a );

  printf("l = %e\n",l);

  unit( &a );

  l = length( &a );

  printf("l = %e\n",l);

  a.y = 0.;
  
  Vec3 b,c;

  b.x = 0.;
  b.y = 4.;
  b.z = 0.;

  crossProduct( &c , &a , &b );

  printf("c.x = %e ; c.y = %e ; c.z = %e \n",c.x,c.y,c.z);
  
  a.x = 1.0;
  a.y = 2.0;
  a.z = 3.0;

  double fac = 3.;

  c = multiplyVector( fac , &a );

  printf("MultiplyVector c.x = %e ; c.y = %e ; c.z = %e \n",c.x,c.y,c.z);
  // Test film

  int h,w;

  h = 200;
  w = 400;

  Film *film = createFilm( h , w ); 

  char imageFileName[40] = "bitmapImage.bmp";

  int i, j;

  Color color;

  for( i= 0 ; i < h ; i++)
  {
    for( j = 0 ; j < w ; j++)
    {
      color.red   = (int)i/(1.0*h)*255;
      color.green = (int)j/(1.0*w)*255;
      color.blue  = (int)(i+j)/(1.0*(h+w))*255;

      storePixelRGB( film , j , i , &color );
    }
  }

  saveToBitmap( film , imageFileName);

  printf("Image generated!!");
}
