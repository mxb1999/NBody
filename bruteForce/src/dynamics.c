#include "brute.h"
#include "math.h"

//update the movement of each particle based upon the forces acting on it
void updateMovement()
{
  for(float t = 0; t < time; t+=dt)
  {
    for (size_t i = 0; i < num; i++) {
      particle* p = sys[i];
      for (size_t j = 0; j < num; j++) {
        if(i!=j)
        {
          particle* q = sys[j];
          float dist = sqrt(pow(p->x-q->x,2) + pow(p->y-q->y,2));
          float force = G*(p->mass)*(q->mass)/dist;
          p->vx += force*dt*(p->x-q->x)/dist;
          p->vy += force*dt*(p->y-q->y)/dist;
        }
      }
      p->x += p->vx*dt;
      p->y += p->vy*dt;
    }
  }

};
