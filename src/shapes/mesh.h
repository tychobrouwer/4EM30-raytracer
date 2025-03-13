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
//  Declaration of the Face type (a face using vectors)
//------------------------------------------------------------------------------


typedef struct 
{
  Vec3       vertices[4];   
  int        vertexCount;
  int        matID;
} Face;


//------------------------------------------------------------------------------
//  Declaration of the FaceData type (a face using vertex IDs)
//------------------------------------------------------------------------------


typedef struct
{
  int        vertexIDs[4];
  int        vertexCount;
  int        matID;
} FaceData;


//------------------------------------------------------------------------------
//  Declaration of the Mesh type (a mesh using vertices and faces)
//------------------------------------------------------------------------------


typedef struct
{
  Vec3       *vertices;
  FaceData   *faces;
  
  int        vertexCount;
  int        faceCount;
} Mesh;


//------------------------------------------------------------------------------
//  readMeshData: Reads the mesh data from a file
//
//  Arguments:
//      fin     : File pointer to the file that contains the mesh data
//      mesh    : Pointer to the mesh
//
//------------------------------------------------------------------------------


void readVertexData

  ( FILE*          fin  ,
    Mesh*          mesh );


//------------------------------------------------------------------------------
//  readFaceData: Reads the face data from a file
//
//  Arguments:
//      fin     : File pointer to the file that contains the face data
//      mesh    : Pointer to the mesh
//
//------------------------------------------------------------------------------


void readFaceData

  ( FILE*          fin  ,
    Mesh*          mesh );


//------------------------------------------------------------------------------
//  getFace: Returns the face with the given face ID from the mesh
//
//  Arguments:
//      face    : Pointer to the face
//      faceID  : ID of the face
//      mesh    : Pointer to the mesh
//
//------------------------------------------------------------------------------


void getFace

  ( Face*         face   ,
    int           faceID ,
    Mesh*         mesh   );


//------------------------------------------------------------------------------
//  addVertex: Adds a vertex to the mesh
//
//  Arguments:
//      mesh    : Pointer to the mesh
//      vertex  : Vertex to be added
//
//  Return:
//      int     : The number of vertices
//
//------------------------------------------------------------------------------


int addVertex

  ( Mesh*         mesh   ,
    Vec3          vertex );


//------------------------------------------------------------------------------
//  addFace: Adds a face to the mesh
//
//  Arguments:
//      mesh        : Pointer to the mesh
//      vertexIDs   : IDs of the vertices of the face
//      vertexCount : Number of vertices of the face
//      matID       : Material ID of the face
//
//  Return:
//      int         : The number of faces
//
//------------------------------------------------------------------------------


int addFace
  
  ( Mesh*         mesh        ,
    int*          vertexIDs   ,
    int           vertexCount ,
    int           matID       );


//------------------------------------------------------------------------------
//  calcFaceIntersection: Calculates the intersection of a ray with a face
//
//  Arguments:
//      intersect : Pointer to the intersection
//      ray       : Pointer to the ray
//      face      : Pointer to the face
//
//  Return:
//      bool      : True if the intersection is found, false otherwise
//
//------------------------------------------------------------------------------


bool calcFaceIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Face*         face      );


//------------------------------------------------------------------------------
// calcTriangleIntersection: Calculates the intersection of a ray with a
//                           triangle defined by a face
//
//  Arguments:
//      intersect : Pointer to the intersection
//      ray       : Pointer to the ray
//      face      : Pointer to the face
//
//  Return:
//      bool      : True if the intersection is found, false otherwise
//
//------------------------------------------------------------------------------


bool calcTriangleIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Face*         face      );
    
    
//------------------------------------------------------------------------------
//  freeMesh: Frees the memory of the mesh
//
//  Arguments:
//      mesh    : Pointer to the mesh
//
//------------------------------------------------------------------------------    
    
    
void freeMesh

  ( Mesh*         mesh );
    

#endif


