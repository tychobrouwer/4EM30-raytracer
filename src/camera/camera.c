/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  04/01/2022 | J.Remmers    | Fixed bug that caused mirroring of image
 *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "camera.h"
#include "../util/mathutils.h"

const char *LOCATION = "Location";
const char *ROTATION = "Rotation";
const char *FOV    = "Fov";

//------------------------------------------------------------------------------
//  readCameraData: Reads the camera data from a file
//------------------------------------------------------------------------------


void readCameraData

  ( FILE*       fin ,
    CameraData* cam )

{
  char label[20] = "None";

  fscanf( fin , "%s" , label );

  while( strcmp( label , "End" ) != 0 )
  {
    if( strcmp( label , LOCATION ) == 0 )
    {
      fscanf( fin , "%le %le %le" , &cam->origin.x , &cam->origin.y , &cam->origin.z );
    }
    else if( strcmp( label , ROTATION ) == 0 )
    {
      fscanf( fin , "%le %le %le" , &cam->rotation.x , &cam->rotation.y , &cam->rotation.z );
    }
    else if ( strcmp( label , FOV ) == 0 )
    {
      fscanf( fin , "%le" , &cam->fov );
    }

    fscanf( fin , "%s" , label );
  }

  printf("  CAMERA\n");
  printf("    Position ................ : %f %f %f \n",cam->origin.x , 
            cam->origin.y , cam->origin.z);
  printf("    Rotation ................ : %f %f %f \n", cam->rotation.x , cam->rotation.y , cam->rotation.z);
  printf("    Field Of View ........... : %f\n",cam->fov);
  printf("\n");  
}


//-----------------------------------------------------------------------------
//  initialiseCamera: Initialises the camera object
//-----------------------------------------------------------------------------


void initialiseCamera
 
  ( CameraData*  cam  ,
    Film*        film )

{
  double height,width;
  double fovrad = cam->fov*PICONST/180.;

  height  = 2.0*tan(0.5*fovrad);
  width   = height*film->width/(1.0*film->height);

  cam->dx = height / (1.0*film->height);
  
  cam->z0 = -0.5*(height-cam->dx);
  cam->y0 =  0.5*(width -cam->dx);
}


//------------------------------------------------------------------------------
//  generateRay: Generates a ray for a given pixel
//------------------------------------------------------------------------------


void generateRay

  ( Ray*          ray ,
    int           ix  ,
    int           iy  ,
    CameraData*   cam )

{
  ray->o.x = cam->origin.x;
  ray->o.y = cam->origin.y;
  ray->o.z = cam->origin.z;
  
  ray->d.x = 1.0;
  ray->d.y = cam->y0-ix*cam->dx;
  ray->d.z = cam->z0+iy*cam->dx;
}
