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

const char *LOCATION = "Centre";
const char *ROTATION = "Rotation";
const char *FOV    = "Fov";
const char *SAMPLE = "Samples";

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
      fscanf( fin , "%le %le %le" , &cam->tilt.x , &cam->tilt.y , &cam->tilt.z);
    }
    else if ( strcmp( label , FOV ) == 0 )
    {
      fscanf( fin , "%le" , &cam->fov );
    }
    else if ( strcmp( label , SAMPLE ) == 0 )
    {
      fscanf( fin , "%d" , &cam->samples_per_pixel );
      printf("DEBUG: Read samples_per_pixel = %d\n", cam->samples_per_pixel);
    }

    fscanf( fin , "%s" , label );
  }

  printf("  CAMERA\n");
  printf("    Location ................ : %f %f %f \n",cam->origin.x , 
            cam->origin.y , cam->origin.z);
  printf("    Rotation ................ : %f %f %f \n", cam->tilt.x , cam->tilt.y , cam->tilt.z);
  printf("    Field Of View ........... : %f\n",cam->fov);
  printf("    Number of samples ........: %d \n", cam->samples_per_pixel);
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
    double        u   ,
    double        v   ,
    CameraData*   cam )

// {for (int sample = 0; sample < cam->samples_per_pixel; sample ++)
  {
  // double u_offset = rand()%1000 / 1000;
  // double v_offset = rand()%1000 / 1000;
  
  double yaw    = cam->tilt.y * PICONST / 180;
  double pitch  = cam->tilt.x * PICONST / 180;
  double roll   = cam->tilt.z * PICONST / 180;

  double cy = cos(yaw),     sy = sin(yaw);
  double cx = cos(pitch), sx = sin(pitch);
  double cz = cos(roll),   sz = sin(roll);


  // double cosY = cos(cam->tilt.y * PICONST / 180);
  // double sinY = sin(cam->tilt.y * PICONST / 180);

  // double cosX = cos(cam->tilt.x * PICONST / 180);
  // double sinX = sin(cam->tilt.x * PICONST / 180);
  ray->o = cam->origin;

  // ray->o.x = cam->origin.x * cosY - cam->origin.z * sinY;
  // // printf("%f %f \n",cam->origin.x , ray->o.x);
  // ray->o.y = cam->origin.y * cosX - cam->origin.z * sinX;
  // ray->o.z = cam->origin.x * sinY * sinX + cam->origin.z * cosY * cosX;
  
  double R[3][3];

  R[0][0] = cy * cz;
  R[0][1] = cy * sz;
  R[0][2] = -sy;

  R[1][0] = sx * sy * cz - cx * sz;
  R[1][1] = sx * sy * sz + cx * cz;
  R[1][2] = sx * cy;

  R[2][0] = cx * sy * cz + sx * sz;
  R[2][1] = cx * sy * sz - sx * cz;
  R[2][2] = cx * cy;


  double dx = 1.0;
  double dy = cam->y0-(ix+u-0.5)*cam->dx;
  double dz = cam->z0+(iy-v-0.5)*cam->dx;

  // double x1 = dx;
  // double y1 = dy * cosPitch - dz *sinPitch;
  // double z1 = dy * sinPitch + dz * cosPitch;

  ray->d.x = R[0][0]*dx + R[0][1]*dy + R[0][2]*dz;
  ray->d.y = R[1][0]*dx + R[1][1]*dy + R[1][2]*dz;
  ray->d.z = R[2][0]*dx + R[2][1]*dy + R[2][2]*dz;

  // ray->d.x = dx*cosY -dz * sinY;
  // ray->d.y = dy*cosX -dz * sinX;
  // ray->d.z = dx * sinY * sinX + dz *cosY * cosX;

  double length = sqrt(ray->d.x * ray->d.x + ray->d.y * ray->d.y + ray->d.z * ray->d.z);
  ray->d.x /= length;
  ray->d.y /= length;
  ray->d.z /= length;
}
// }