/*------------------------------------------------------------------------------
 *  Spotlight input reader for RayTracer (4EM30 - TU/e)
 *  Author: Joris Remmers, optimized version 2025
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "spotlight.h"

#define PI 3.14159265358979323846

//------------------------------------------------------------------------------
//  readSpotlightData: Reads all spotlight definitions from the input file
//------------------------------------------------------------------------------

void readSpotlightData(FILE *fin, Spotlights *spotlights)
{
  char label[32];

  int nLight;
  fscanf(fin, "%d", &nLight);
  
  spotlights->spotlight = (Spotlight *)malloc(sizeof(Spotlight) * nLight);
  spotlights->count = 0;

  for (int i = 0; i < nLight; ++i)
  {
    Vec3 coord;
    Vec3 dir;
    double intensity, cutoffDeg, sharpness;

    fscanf(fin, "%le %le %le %le %le %le %le %le %le", &coord.x, &coord.y, &coord.z, &dir.x, &dir.y, &dir.z, &intensity, &cutoffDeg, &sharpness);

    unit(&dir);

    int id = addLight(spotlights, coord, dir, intensity, cutoffDeg, sharpness);
  }

  printf("    Number of lights ........ : %d\n",nLight);
}

//------------------------------------------------------------------------------
//  addLight: Helper function to add a new spotlight
//------------------------------------------------------------------------------


int addLight(Spotlights *spotlights, Vec3 coord, Vec3 dir, double intensity, double cutoffDeg, double sharpness)
{
    int id = spotlights->count;

    double cutoffRad = cutoffDeg * (PI / 180.0);
    
  spotlights->spotlight[id].coord = coord;
    spotlights->spotlight[id].dir = dir;
    spotlights->spotlight[id].intensity = intensity;
    spotlights->spotlight[id].cosCutoff = cos(cutoffRad);
    spotlights->spotlight[id].sharpness = sharpness;

    spotlights->count++;
    return id;
}
