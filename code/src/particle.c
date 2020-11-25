#include "particle.h"
vector2* newVector2(float x, float z)
{
  vector2* this = (vector2*)malloc(sizeof(vector2));
  if(this == NULL)
  {
    return NULL;
  }
  this->x = x;
  this->z = z;
  return this;
};

particle* new_particle(float x, float z, float vx, float vz, float m)
{
  particle* this = (particle*)malloc(sizeof(particle));
  if(this == NULL)
  {
    return NULL;
  }
  this->pos[0] = x;
  this->pos[1] = z;
  this->force[0] = 0;
  this->force[1] = 0;
  this->v[0] = vx;
  this->v[1] = vz;
  this->mass = m;
  return this;
};//constructor
//Accessor functions for particle struct
float particle_getX(particle* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->pos[0];
};
float particle_getZ(particle* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->pos[1];
};
float particle_getVX(particle* this){
  if(this == NULL)
  {
    return -1;
  }
  return this->v[0];
};
float particle_getVZ(particle* this){
  if(this == NULL)
  {
    return -1;
  }
  return this->v[1];
};
float particle_getMass(particle* this){
  if(this == NULL)
  {
    return -1;
  }
  return this->mass;
};
