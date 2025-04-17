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
#include <stdlib.h>
#include <assert.h>

#include "../util/vector.h"
#include "../util/film.h"
#include "../util/bvh.h"
#include "../shapes/shapes.h"
#include "../shapes/spheres.h"
#include "../util/vector.h"

// Test computeFaceAABB
void test_computeFaceAABB() {
  Face face;
  face.vertexCount = 3;
  face.vertices[0] = (Vec3){0.0, 0.0, 0.0};
  face.vertices[1] = (Vec3){1.0, 0.0, 0.0};
  face.vertices[2] = (Vec3){0.0, 1.0, 0.0};

  AABB aabb = computeFaceAABB(&face);

  assert(aabb.min.x == 0.0 && aabb.min.y == 0.0 && aabb.min.z == 0.0);
  assert(aabb.max.x == 1.0 && aabb.max.y == 1.0 && aabb.max.z == 0.0);

  printf("test_computeFaceAABB passed.\n");
}

// Test computeSphereAABB
void test_computeSphereAABB() {
  Sphere sphere;
  sphere.centre = (Vec3){1.0, 1.0, 1.0};
  sphere.radius = 2.0;

  AABB aabb = computeSphereAABB(&sphere);

  assert(aabb.min.x == -1.0 && aabb.min.y == -1.0 && aabb.min.z == -1.0);
  assert(aabb.max.x == 3.0 && aabb.max.y == 3.0 && aabb.max.z == 3.0);

  printf("test_computeSphereAABB passed.\n");
}

// Test computeCentroidAABB
void test_computeCentroidAABB() {
  AABB aabb;
  aabb.min = (Vec3){0.0, 0.0, 0.0};
  aabb.max = (Vec3){2.0, 2.0, 2.0};

  Vec3 centroid = computeCentroidAABB(&aabb);

  assert(centroid.x == 1.0 && centroid.y == 1.0 && centroid.z == 1.0);

  printf("test_computeCentroidAABB passed.\n");
}

// Test traverseBVH
void test_traverseBVH() {
  Globdat globdat;
  BVH *bvh = (BVH *)malloc(sizeof(BVH));
  bvh->nodeCount = 0;

  globdat.spheres.count = 2;
  globdat.spheres.sphere[0].centre = (Vec3){0.0, 0.0, 0.0};
  globdat.spheres.sphere[0].radius = 1.0;
  globdat.spheres.sphere[0].matID = 1;
  globdat.spheres.sphere[1].centre = (Vec3){10.0, 10.0, 5.0};
  globdat.spheres.sphere[1].radius = 1.0;
  globdat.spheres.sphere[1].matID = 2;
  globdat.mesh.faceCount = 0;

  buildBVH(bvh, &globdat, 0, globdat.spheres.count);

  assert(bvh->nodeCount == 1);

  Ray ray;
  ray.o = (Vec3){0.0, 0.0, 5.0};
  ray.d = (Vec3){0.0, 0.0, -1.0};
  unit(&ray.d);

  Intersect intersection;
  resetIntersect(&intersection);

  traverseBVH(bvh, &globdat, &ray, &intersection);

  assert(intersection.matID == 1);
  assert(intersection.t == 4.0);

  printf("test_traverseBVH passed.\n");
}

int main( void )

{
  // Test Vector utilities

  Vec3 a;

  a.x = 3.0;
  a.y = 4.0;
  a.z = 0.0;

  double l = length( &a );

  printf("l = %e\n",l);

  unit( &a );

  l = length( &a );

  printf("l = %e\n",l);

  a.y = 0.;
  
  Vec3 b,c;

  b.x = 0.;
  b.y = 4.;
  b.z = 0.;

  crossProduct( &c , &a , &b );

  printf("c.x = %e ; c.y = %e ; c.z = %e \n",c.x,c.y,c.z);
  
  a.x = 1.0;
  a.y = 2.0;
  a.z = 3.0;

  double fac = 3.;

  c = multiplyVector( fac , &a );

  printf("MultiplyVector c.x = %e ; c.y = %e ; c.z = %e \n",c.x,c.y,c.z);
  // Test film

  int h,w;

  h = 200;
  w = 400;

  Film *film = createFilm( h , w ); 

  char imageFileName[40] = "bitmapImage.bmp";

  int i, j;

  Color color;

  for( i= 0 ; i < h ; i++)
  {
    for( j = 0 ; j < w ; j++)
    {
      color.red   = (int)i/(1.0*h)*255;
      color.green = (int)j/(1.0*w)*255;
      color.blue  = (int)(i+j)/(1.0*(h+w))*255;

      storePixelRGB( film , j , i , &color );
    }
  }

  saveToBitmap( film , imageFileName);

  test_computeFaceAABB();
  test_computeSphereAABB();
  test_computeCentroidAABB();
  test_traverseBVH();

  printf("Image generated!!\n");
}
