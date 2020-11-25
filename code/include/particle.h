#include <math.h>
#include <stdlib.h>
#include <omp.h>
#ifndef PARTICLE
#define PARTICLE
  #define G 6.674e-11
  #define PI 3.141592653
  #define THETA 1
  typedef struct
  {
    float x;
    float z;
  }vector2;//shorthand for storing vector quantities in 2 dimensions
  typedef struct {
    double pos[2];//2D position vector
    double v[2];//2D velocity vector
    double force[2];//cumulative force vector
    double mass;//particle mass
  } particle;

  extern particle* new_particle(float x, float z, float vx, float vz, float m);//constructor
  //Accessor functions for particle struct
  extern float particle_getX(particle* this);
  extern float particle_getZ(particle* this);
  extern float particle_getVX(particle* this);
  extern float particle_getVZ(particle* this);
  extern float particle_getMass(particle* this);

  #define dist(px, pz, cx, cz) sqrt(pow(px-cx,2)+pow(pz-cz,2))//Macro for calculating the distance between two points (namely a COM location and a particle)
  #define distsq(px, pz, cx, cz) pow(px-cx,2)+pow(pz-cz,2)
#endif
