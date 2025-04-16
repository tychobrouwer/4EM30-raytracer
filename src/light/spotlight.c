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
#include <stdlib.h>
#include "spotlight.h"
#define PI 3.14159265358979323846


//------------------------------------------------------------------------------
//  readspotlightData: Reads the spotlight data from a file
//------------------------------------------------------------------------------

void readSpotlightData(FILE *fin, Spotlights *spotlights)

{
  int nLight = 0;
  Vec3 coord;
  double intensity, cutoff, falloffSharpness;

  fscanf(fin, "%d", &nLight);

  spotlights->spotlight = (Spotlight*)malloc(nLight * sizeof(Spotlight));
  spotlights->count = 0;

  for (int iLight = 0; iLight < nLight; iLight++)
  {
    fscanf(fin, "%le %le %le %le", &coord.x, &coord.y, &coord.z, &intensity);
    fscanf(fin, "%le %le", &cutoff, &falloffSharpness);
    cutoff = cutoff * (PI / 180.0);  // convert degrees → radians

    int id = addLight(spotlights, coord, intensity);
    spotlights->spotlight[id].cutoff = cutoff;
    spotlights->spotlight[id].falloffSharpness = falloffSharpness;
  }

}

int addLight(Spotlights* spotlights, Vec3 coord, double intensity)
{
    int spotlightID = spotlights->count;

    spotlights->spotlight[spotlightID].coord = coord;
    spotlights->spotlight[spotlightID].intensity = intensity;

    spotlights->count++;
    return spotlightID;
}

