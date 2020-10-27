#include "brute.h"
#include <string.h>

char* fileIn;
particle** sys;
float totalTime;
float time;
int num;
float dt;

particle* new_Particle(char* info)
{
  if(info != NULL)
  {
    return NULL;
  }
  char* a;
  char* b;
  particle* this = (particle*)malloc(sizeof(particle));
  if(this == NULL)
  {
    return NULL;
  }
  this->x = strtof(info, &a);
  this->y = strtof(a, &b);
  this->vx = strtof(b, &a);
  this->vy = strtof(a, &b);
  this->mass = strtof(b, &a);
  return this;
}
//read and update arrays with initial information
void readFile()
{
  FILE *in = fopen(fileIn, "r");
  if(in == NULL)
  {
    printf("%s\n", "File not found");
    return;
  }
  char buff[255];
  //first value is number of inputs
  fscanf(in, "%d",&num);
  //second value is time to be simulated
  fscanf(in, "%f",&time);
  //final value is time step
  fscanf(in, "%f", &dt);
  //look at next line
  fgets(buff, 255, (FILE*)in);
  sys = (particle**)malloc(sizeof(particle*)*num);
  int count = 0;
  while(*fgets(buff, 255, (FILE*)in)!= EOF)
  {
    sys[count] = new_Particle(buff);
  }
};
//output results to python for plotting
void outputVis();
