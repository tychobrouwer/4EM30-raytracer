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
 
 #include <stdbool.h>
 #include "../util/vector.h"


 
 //------------------------------------------------------------------------------
 //  Declaration of the Spotlight type (a spotlight)
 //------------------------------------------------------------------------------
 
 
 typedef struct 
 {
   Vec3 coord;
   double cutoff;
   double falloffSharpness;
   double intensity;
 } Spotlight;



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
 int addLight(Spotlights* spotlights, Vec3 coord, double intensity);

  #endif



 