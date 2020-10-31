#include <stdlib.h>
#include <stdio.h>
#include "staticTree.h"
#ifndef GALSIM
/*
  Barnes-Hut simulation algorithm
  Relate forces by COM arguments, nlogn runtime

*/
//zone used to store particle and mass info within barnes-hut tree
typedef struct
{
  float centerX;
  float centerZ;
  float boundX;
  float boundZ;
  float m;
}zone;
extern zone* newZone(float x, float z, float xb, float zb, float m);
extern
  extern float G;//mks gravitational constant
  extern float pi;//maximum precision pi for 4B floating point
#endif
