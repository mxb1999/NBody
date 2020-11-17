#include <stdlib.h>
#include <stdio.h>
#include "staticTree.h"
#include <time.h>
#ifndef GALSIM
  #define GALSIM
  /*
    Barnes-Hut simulation algorithm
    Relate forces by COM arguments, nlogn runtime

  */
  //Struct definition for an individual particle


  extern vector2* newVector2(float x, float z);


  //zone used to store zone and COM infor within barnes-hut tree
  typedef struct
  {
    vector2 center;//position of zone center
    vector2 COM;//position of zone center of mass
    vector2 centerV;//velocity of the particle within the zone, if only one.
    float bound;//defines the bound of the zone, note that this assumes a square bound
    float m;//mass of particle in zone, or reduced mass of all particles within zone
    particle* particle;//pointer to particle within zone, NULL if none
  }zone;
  extern zone* newZone(float x, float z, float b,float m);//constructor function for zones
  //external accessor functions
  extern float zone_getX(zone* this);
  extern float zone_getZ(zone* this);
  extern float zone_getVX(zone* this);
  extern float zone_getVZ(zone* this);
  extern float zone_bound(zone* this);
  extern float zone_massTotal(zone* this);
  extern particle* getParticle(zone* this);//returns the particle stored, returns NULL if none
  //functions to adjust zone values
  extern void setCOM(node* this);//recursively descend tree and rebalance the COM parameters
  extern zone* readInBH(char* fileName);//read input parameters from a given filename


/*PARTICLE MESH CODE*/

#endif
