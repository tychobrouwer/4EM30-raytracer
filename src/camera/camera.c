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
#include <stdlib.h>
#include <string.h>
#include "camera.h"
#include "../util/mathutils.h"

const char *LOCATION = "Centre";
const char *ROTATION = "Rotation";
const char *FOV    = "Fov";
const char *SAMPLE = "Samples";
const char *STRATIFIED = "Stratified";
const char *APERTURE = "Aperture";
const char *FOCAL_LENGTH = "Focallength";

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
    }
    else if ( strcmp( label , STRATIFIED ) == 0 )
    {
      fscanf( fin , "%d" , &cam->strat );
    }
    else if (strcmp(label, APERTURE) == 0) {
      fscanf(fin, "%le", &cam->aperture);
    }
    else if (strcmp(label, FOCAL_LENGTH) == 0) {
        fscanf(fin, "%le", &cam->focal_length);
    }

    fscanf( fin , "%s" , label );
  }

  printf("  CAMERA\n");
  printf("    Location ................ : %f %f %f \n",cam->origin.x , 
            cam->origin.y , cam->origin.z);
  printf("    Rotation ................ : %f %f %f \n", cam->tilt.x , cam->tilt.y , cam->tilt.z);
  printf("    Field Of View ........... : %f\n",cam->fov);
  printf("    Number of samples ........: %d \n", cam->samples_per_pixel);
  printf("    Sampling, 1 for stratified, 0 for random = %d\n", cam->strat);
  printf("    Camera aperture = %d\n", cam->aperture);
  printf("    Camera focal length = %d\n", cam->focal_length);



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

  {
  double lens_radius = 0.5 * cam->aperture;
  double r1, r2;
  // create disc with random point r1 and r2 on it.
  do {
    r1 = 2.0 * rand() / (double)RAND_MAX - 1.0;
    r2 = 2.0 * rand() / (double)RAND_MAX - 1.0;
  } while (r1 * r1 + r2 * r2 > 1.0);

  double lens_x = lens_radius * r1;
  double lens_y = lens_radius * r2;
  
  //convert input angles to radians
  double yaw    = cam->tilt.y * PICONST / 180;
  double pitch  = cam->tilt.x * PICONST / 180;
  double roll   = cam->tilt.z * PICONST / 180;

  // calculate cosine and sine of angles
  double cy = cos(yaw),     sy = sin(yaw);
  double cx = cos(pitch), sx = sin(pitch);
  double cz = cos(roll),   sz = sin(roll);

  ray->o = cam->origin;

  // Define 3x3 rotation matrix
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
  double dy = cam->y0-(ix+u)*cam->dx;
  double dz = cam->z0+(iy-v)*cam->dx;

  // set the direction of the rays using the lens
  double dir_x = dx * cam->focal_length;
  double dir_y = dy * cam->focal_length;
  double dir_z = dz * cam->focal_length;
  
// Rotate direction
double dir_rot_x = R[0][0]*dir_x + R[0][1]*dir_y + R[0][2]*dir_z;
double dir_rot_y = R[1][0]*dir_x + R[1][1]*dir_y + R[1][2]*dir_z;
double dir_rot_z = R[2][0]*dir_x + R[2][1]*dir_y + R[2][2]*dir_z;

// Calculate the offset by the lens
double offset_x = R[0][0]*lens_x + R[0][1]*lens_y;
double offset_y = R[1][0]*lens_x + R[1][1]*lens_y;
double offset_z = R[2][0]*lens_x + R[2][1]*lens_y;

// Set the origin of the ray equal to that of the camera plus the lens
ray->o.x = cam->origin.x + offset_x;
ray->o.y = cam->origin.y + offset_y;
ray->o.z = cam->origin.z + offset_z;

// Determine the direction of the rays
ray->d.x = dir_rot_x - offset_x;
ray->d.y = dir_rot_y - offset_y;
ray->d.z = dir_rot_z - offset_z;

// normalize the vectors
  double length = sqrt(ray->d.x * ray->d.x + ray->d.y * ray->d.y + ray->d.z * ray->d.z);
  ray->d.x /= length;
  ray->d.y /= length;
  ray->d.z /= length;
}
// }