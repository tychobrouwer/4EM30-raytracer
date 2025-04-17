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
    int useCutoff = 1;     // default to ON
    int useFalloff = 1;

    char label[32];

    // Read optional global flags
    for (int i = 0; i < 2; ++i) {
        if (fscanf(fin, "%s", label) != 1) break;

        if (strcmp(label, "UseCutoff") == 0) {
            fscanf(fin, "%d", &useCutoff);
        } else if (strcmp(label, "UseFalloff") == 0) {
            fscanf(fin, "%d", &useFalloff);
        } else {
            // Rewind label to parse number of lights next
            fseek(fin, -strlen(label), SEEK_CUR);
            break;
        }
    }

    int nLight;
    if (fscanf(fin, "%d", &nLight) != 1 || nLight <= 0) {
        printf("Error: Invalid number of spotlights.\n");
        return;
    }

    spotlights->spotlight = (Spotlight *)calloc(nLight, sizeof(Spotlight));
    if (!spotlights->spotlight) {
        printf("Error: Could not allocate memory for spotlights.\n");
        exit(EXIT_FAILURE);
    }

    spotlights->count = 0;

    for (int i = 0; i < nLight; ++i) {
        Vec3 coord;
        double intensity, cutoffDeg, falloffSharpness;

        if (fscanf(fin, "%le %le %le %le", &coord.x, &coord.y, &coord.z, &intensity) != 4 ||
            fscanf(fin, "%le %le", &cutoffDeg, &falloffSharpness) != 2) {
            printf("Error: Could not read spotlight parameters.\n");
            exit(EXIT_FAILURE);
        }

        double cutoffRad = cutoffDeg * (PI / 180.0);
        

        int id = addLight(spotlights, coord, intensity);
        spotlights->spotlight[id].cutoff = cutoffRad;
        spotlights->spotlight[id].cosCutoff = cos(cutoffRad);  // ← Precompute here
        spotlights->spotlight[id].falloffSharpness = falloffSharpness;
        spotlights->spotlight[id].useCutoff = (useCutoff != 0);
        spotlights->spotlight[id].useFalloff = (useFalloff != 0);
    }
}
 
 //------------------------------------------------------------------------------
 //  addLight: Helper function to add a new spotlight
 //------------------------------------------------------------------------------
 
 int addLight(Spotlights *spotlights, Vec3 coord, double intensity)
 {
     int id = spotlights->count;
 
     spotlights->spotlight[id].coord = coord;
     spotlights->spotlight[id].intensity = intensity;
 
     spotlights->count++;
     return id;
 }