/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  04/01/2022 | J.Remmers    | New datastructure for faces
 *  12/02/2023 | J.Remmers    | Added new instructions for students / cleaning
 *                            |   up the code (removing unused magic numbers)
 *----------------------------------------------------------------------------*/

#ifndef SHAPES_MESH_H
#define SHAPES_MESH_H

#include <stdbool.h>
#include "../util/vector.h"
#include "../util/ray.h"


//------------------------------------------------------------------------------
//  TODO: COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       vertices[4];   
  int        vertexCount;
  int        matID;
} Face;


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


typedef struct
{
  int        vertexIDs[4];
  int        vertexCount;
  int        matID;
} FaceData;


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


typedef struct
{
  Vec3       *vertices;
  FaceData   *faces;
  
  int        vertexCount;
  int        faceCount;
} Mesh;


//------------------------------------------------------------------------------
//  TODO: COMPLETE FUNCTION DESCRIPTIONS AND CONTRACTS
//------------------------------------------------------------------------------


void readVertexData

  ( FILE*          fin  ,
    Mesh*          mesh );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void readFaceData

  ( FILE*          fin  ,
    Mesh*          mesh );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void getFace

  ( Face*         face   ,
    int           faceID ,
    Mesh*         mesh   );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


int addVertex

  ( Mesh*         mesh   ,
    Vec3          vertex );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


int addFace
  
  ( Mesh*         mesh        ,
    int*          vertexIDs   ,
    int           vertexCount ,
    int           matID       );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


bool calcFaceIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Face*         face      );


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


bool calcTriangleIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Face*         face      );
    
    
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------    
    
    
void freeMesh

  ( Mesh*         mesh );
    

#endif


