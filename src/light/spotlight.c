/*------------------------------------------------------------------------------
 *  Spotlight input reader for RayTracer (4EM30 - TU/e)
 *  Author: Joris Remmers, optimized version 2025
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
        double intensity, cutoffDeg, falloffSharpness;

        fscanf(fin, "%le %le %le %le %le %le %le", &coord.x, &coord.y, &coord.z, &dir.x, &dir.y, &dir.z, &intensity);
        fscanf(fin, "%le %le", &cutoffDeg, &falloffSharpness);

        double cutoffRad = cutoffDeg * (PI / 180.0);

        unit(&dir);

        int id = addLight(spotlights, coord, dir, intensity);
        spotlights->spotlight[id].cutoff = cutoffRad;
        spotlights->spotlight[id].cosCutoff = cos(cutoffRad);
        spotlights->spotlight[id].falloffSharpness = falloffSharpness;
    }
}

//------------------------------------------------------------------------------
//  addLight: Helper function to add a new spotlight
//------------------------------------------------------------------------------

int addLight(Spotlights *spotlights, Vec3 coord, Vec3 dir, double intensity)
{
    int id = spotlights->count;

    spotlights->spotlight[id].coord = coord;
    spotlights->spotlight[id].dir = dir;
    spotlights->spotlight[id].intensity = intensity;

    spotlights->count++;
    return id;
}