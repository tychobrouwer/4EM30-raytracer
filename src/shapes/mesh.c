/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2024 Joris Remmers, TU/e
 *
 *  Versions:
 *  03/02/2020 | J.Remmers    | First version
 *  04/01/2022 | J.Remmers    | New data structure for faces
 *  12/02/2023 | J.Remmers    | Cleaning up code
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "../util/mathutils.h"


//------------------------------------------------------------------------------
//  readMeshData: Reads the mesh data from a file
//------------------------------------------------------------------------------


void readVertexData

  ( FILE*       fin  ,
    Mesh*       mesh )

{
  int iVer;
  int nVer = 0;

  Vec3   vertex;

  fscanf( fin , "%d" , &nVer );
  
  mesh->vertices = (Vec3*)malloc(nVer * sizeof(Vec3));
  mesh->VertexNormal = (Vec3*)calloc(nVer, sizeof(Vec3));

  for( iVer = 0 ; iVer < nVer ; iVer++ )
  {
    fscanf( fin , "%le %le %le" , &vertex.x , &vertex.y , &vertex.z );
    
    addVertex( mesh , vertex );
  }

  printf("    Number of vertices ...... : %d\n",nVer);
}


//-----------------------------------------------------------------------------
//  readFaceData: Reads the face data from a file
//-----------------------------------------------------------------------------


void readFaceData

  ( FILE*       fin  ,
    Mesh*       mesh )

{
  int iFac,iVer;
  int nFac  = 0;
  int nVer  = 0;
  int matID = 0;

  int face[4];

  fscanf( fin , "%d" , &nFac );
  
  mesh->faces = (FaceData*)malloc(nFac * sizeof(FaceData));

  for( iFac = 0 ; iFac < nFac ; iFac++ )
  {
    fscanf( fin , "%d %d" , &matID , &nVer );
    
    for ( iVer = 0 ; iVer < nVer ; iVer++ )
    {
      fscanf( fin , "%d" , &face[iVer] );
    }
    
    addFace( mesh , face , nVer , matID );
  }

  printf("    Number of faces ......... : %d\n",nFac);
}


//-----------------------------------------------------------------------------
//  getFace: Returns the face with the given face ID from the mesh
//-----------------------------------------------------------------------------


void getFace

  ( Face*    face   ,
    int      faceID ,
    Mesh*    mesh   )

{
  int i,iCrd;

  face->matID       = mesh->faces[faceID].matID;
  face->vertexCount = mesh->faces[faceID].vertexCount;
  
  for ( i = 0 ; i < face->vertexCount ; i++ )
  {  
    iCrd = mesh->faces[faceID].vertexIDs[i];
    face->vertices[i] = mesh->vertices[iCrd];
  }
}


//-----------------------------------------------------------------------------
//  addVertex: Adds a vertex to the mesh
//-----------------------------------------------------------------------------
  

int addVertex

  ( Mesh*    mesh ,
    Vec3     v    )

{
  int i = mesh->vertexCount;

  mesh->vertices[i].x = v.x;
  mesh->vertices[i].y = v.y;
  mesh->vertices[i].z = v.z;

  mesh->vertexCount++;

  return i;
}


//-----------------------------------------------------------------------------
//  addFace: Adds a face to the mesh
//-----------------------------------------------------------------------------


int addFace
  
  ( Mesh*    mesh        ,
    int*     vertexIDs   ,
    int      vertexCount ,
    int      matID       )

{
  int i = mesh->faceCount;

  mesh->faces[i].vertexCount = vertexCount;
  mesh->faces[i].matID       = matID;

  for ( int j = 0 ; j < vertexCount ; j++ )
  {  
    mesh->faces[i].vertexIDs[j] = vertexIDs[j];
  }

  mesh->faceCount++;

  return i;
}


//-----------------------------------------------------------------------------
//  calcFaceIntersection: Calculates the intersection of a ray with a face
//-----------------------------------------------------------------------------


bool calcFaceIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Face*         face      ,
    Mesh*         mesh      ,
    int           iShp      )

{
  bool tlabel;
  if ( face->vertexCount == 3 )
  {
    tlabel =true;
    return calcTriangleIntersection( intersect , ray , face, mesh, iShp, tlabel);
  }
  else
  {
    tlabel = false;
    Face triaFace;
    bool flag;

    triaFace.matID       = face->matID;
    triaFace.vertexCount = 3;
   
    triaFace.vertices[0]  = face->vertices[0];
    triaFace.vertices[1]  = face->vertices[1];
    triaFace.vertices[2]  = face->vertices[2];

    flag = calcTriangleIntersection( intersect , ray , &triaFace, mesh, iShp, tlabel);

    if (flag)
    {
      return true;
    }
    else
    {
      tlabel = true;
      triaFace.vertices[0]  = face->vertices[0];
      triaFace.vertices[1]  = face->vertices[2];
      triaFace.vertices[2]  = face->vertices[3];
      
      return calcTriangleIntersection( intersect , ray , &triaFace, mesh, iShp, tlabel);
    }
  }

  return false;
}


//-----------------------------------------------------------------------------
// calcTriangleIntersection: Calculates the intersection of a ray with a
//                           triangle defined by a face
//-----------------------------------------------------------------------------


bool calcTriangleIntersection

  ( Intersect*    intersect ,
    Ray*          ray       ,
    Face*         face      ,
    Mesh*         mesh      ,
    int           iShp      ,
    bool          tlabel    )

{
  Vec3 p0t,p1t,p2t,d;

  p0t = addVector( 1.0 , &face->vertices[0] , -1.0 , &ray->o );
  p1t = addVector( 1.0 , &face->vertices[1] , -1.0 , &ray->o );
  p2t = addVector( 1.0 , &face->vertices[2] , -1.0 , &ray->o );

  int kz = maxDimension(&ray->d);
  int kx = kz + 1; 

  if (kx == 3)
  {
    kx = 0;
  }
  
  int ky = kx + 1; 

  if (ky == 3) 
  { 
    ky = 0;
  }

  d   = permute(ray->d, kx, ky, kz );
  p0t = permute(p0t   , kx, ky, kz );
  p1t = permute(p1t   , kx, ky, kz );
  p2t = permute(p2t   , kx, ky, kz );
  
  double sx = -d.x/d.z;
  double sy = -d.y/d.z;
  double sz = 1.0 /d.z;

  p0t.x += sx * p0t.z;
  p0t.y += sy * p0t.z;
  p1t.x += sx * p1t.z;
  p1t.y += sy * p1t.z;
  p2t.x += sx * p2t.z;
  p2t.y += sy * p2t.z;

  double e0 = p1t.x*p2t.y - p1t.y*p2t.x;
  double e1 = p2t.x*p0t.y - p2t.y*p0t.x;
  double e2 = p0t.x*p1t.y - p0t.y*p1t.x;

  if ( ( e0<0 || e1<0 || e2<0 ) && ( e0>0 || e1>0 || e2>0 ) )
  {
    return false;
  }
  
  double det = e0 + e1 + e2;

  if ( det == 0 )
  {
    return false;
  }
  
  p0t.z *= sz;
  p1t.z *= sz;
  p2t.z *= sz;

  double tScaled = e0*p0t.z + e1*p1t.z + e2*p2t.z;

  if( det < 0 && ( tScaled >= 0 || tScaled < intersect->t*det ) )
  {
    return false;
  }
  else if( det > 0 && ( tScaled <= 0 || tScaled > intersect->t*det ) )
  {
    return false;
  }

  intersect->t  = tScaled / det;

  intersect->matID = face->matID;

  Vec3 Vertexn1, Vertexn2, Vertexn3;

  if (tlabel)
  {
    Vertexn1 = mesh->VertexNormal[mesh->faces[iShp].vertexIDs[0]];
    Vertexn2 = mesh->VertexNormal[mesh->faces[iShp].vertexIDs[2]];
    Vertexn3 = mesh->VertexNormal[mesh->faces[iShp].vertexIDs[3]];
  }
  else
  {
    Vertexn1 = mesh->VertexNormal[mesh->faces[iShp].vertexIDs[0]];
    Vertexn2 = mesh->VertexNormal[mesh->faces[iShp].vertexIDs[1]];
    Vertexn3 = mesh->VertexNormal[mesh->faces[iShp].vertexIDs[2]];
  }

  float a = e0 / det;
  float b = e1 / det;
  float c = 1.0f - a - b;

  intersect->normal.x = a * Vertexn1.x + b * Vertexn2.x + c * Vertexn3.x;
  intersect->normal.y = a * Vertexn1.y + b * Vertexn2.y + c * Vertexn3.y;
  intersect->normal.z = a * Vertexn1.z + b * Vertexn2.z + c * Vertexn3.z;

  unit(&intersect->normal);
  return true;
}

//------------------------------------------------------------------------------
//  freeMesh: Frees the memory of the mesh
//------------------------------------------------------------------------------

  
void freeMesh

  ( Mesh*       mesh )

{
  free ( mesh->faces );
  free ( mesh->vertices );
}
