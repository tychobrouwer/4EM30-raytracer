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
#include <string.h>
#include "spotlight.h"

//------------------------------------------------------------------------------
//  readspotlightData: Reads the spotlight data from a file
//------------------------------------------------------------------------------

void readSpotlightData

    (FILE *fin,
     Spotlights *spotlights)

{
  int nLight = 0;
  Vec3 coord;
  double intensity;
  int iLight;

  fscanf(fin, "%d", &nLight);

  for (iLight = 0; iLight < nLight; iLight++)
  {
    fscanf(fin, "%le %le %le %le", &coord.x,
           &coord.y, &coord.z,
           &intensity);

    addLight(spotlights, coord, intensity);
  }

  printf("    Number of spotlights .... : %d\n", spotlights->count);
}

int addLight(Spotlights *spotlights, Vec3 coord, double intensity)
{

  int spotlightID = spotlights->count;

  spotlights->spotlight[spotlightID].coord.x = coord.x;
  spotlights->spotlight[spotlightID].coord.y = coord.y;
  spotlights->spotlight[spotlightID].coord.z = coord.z;
  spotlights->spotlight[spotlightID].intensity = intensity;

  spotlights->count++;

  return spotlightID;
}