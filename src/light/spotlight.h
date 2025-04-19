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

 #ifndef LIGHT_SPOTLIGHT_H
 #define LIGHT_SPOTLIGHT_H
 
 #include "../util/vector.h"


 //------------------------------------------------------------------------------
 //  Declaration of the Spotlight type (a spotlight)
 //------------------------------------------------------------------------------
 
 typedef struct 
 {
   Vec3 coord;
   Vec3 dir;
   double sharpness;
   double intensity;
   double cosCutoff;
 } Spotlight;

 //------------------------------------------------------------------------------
 //  Declaration of the Spotlights type (for count calculation)
 //------------------------------------------------------------------------------

 typedef struct 
 {
     Spotlight *spotlight;
     int count;
 } Spotlights;

 
 //------------------------------------------------------------------------------
 //  readSpotlightData: Reads the spotlight data from a file
 //
 //  Arguments:
 //      fin     : File pointer to the file that contains the spotlight data
 //      spotlight     : Pointer to the spotlight
 //
 //------------------------------------------------------------------------------
 
 
 void readSpotlightData( FILE* fin, Spotlights *spotlights );

 //------------------------------------------------------------------------------
 //  addLight: Adds a spotlight to the Spotlights array with given parameters
 //
 //  Arguments:
 //      spotlights        : Pointer to the Spotlights struct where the light will be added
 //      coord             : The position of the spotlight (Vec3)
 //      dir               : The direction the spotlight is pointing (Vec3)
 //      intensity         : The intensity of the spotlight
 //      cutoff            : Degrees of the cone
 //      sharpness         : Sharpness of the shadow falloff
 //
 //  Return:
 //      int               : The new total count of spotlights after adding the new one
 //------------------------------------------------------------------------------

 int addLight(Spotlights* spotlights, Vec3 coord, Vec3 dir, double intensity, double cutoff, double sharpness);

  #endif



 
