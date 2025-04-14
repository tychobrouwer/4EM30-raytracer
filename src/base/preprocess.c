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

#include "preprocess.h"


//------------------------------------------------------------------------------
//  preprocess: Preprocesses the data
//------------------------------------------------------------------------------


void preprocess

  ( Globdat  *globdat )

{
  initialiseCamera( &globdat->cam , globdat->film );
  calcVertexNormal ( &globdat ->mesh);
}


//-------------------------------------------------------------
// calcVertexNormal
//-------------------------------------------------------------

void calcVertexNormal( Mesh* mesh )
{
  int vertexID;

  for (int i = 0; i < mesh->vertexCount; i++)
  {
    mesh->VertexNormal[i].x = 0;
    mesh->VertexNormal[i].y = 0;
    mesh->VertexNormal[i].z = 0;
  }

  for (int i = 0; i < mesh->faceCount; i++)
  {
    int* vertexIDs = mesh->faces[i].vertexIDs;

    Vec3 v1 = mesh->vertices[vertexIDs[0]];
    Vec3 v2 = mesh->vertices[vertexIDs[1]];
    Vec3 v3 = mesh->vertices[vertexIDs[2]];

    Vec3 a = addVector(1.0, &v2, -1.0, &v1);
    Vec3 b = addVector(1.0, &v3, -1.0, &v1);

    Vec3 faceNormal;
    crossProduct(&faceNormal, &a, &b);
    unit(&faceNormal);

    for (int j = 0; j < mesh->faces[i].vertexCount; j++)
    {
      vertexID = vertexIDs[j];
      mesh->VertexNormal[vertexID] = addVector(1.0, &mesh->VertexNormal[vertexID], 1.0, &faceNormal);
    }
  }

  for (int i = 0; i < mesh->vertexCount; i++)
  {
    unit(&mesh->VertexNormal[i]);
  }
}
