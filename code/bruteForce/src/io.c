#include "brute.h"
#include <string.h>

char* fileIn;
particle** sys;
float totalTime;
float time;
int num;
float dt;


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
  if(fscanf(in, "%d",&num) && fscanf(in, "%f",&time)
    && fscanf(in, "%f",&dt))
    {
      printf("%s\n", "Inputs read correctly");
    }

  char* temp = fgets(buff, 255, (FILE*)in);
  sys = (particle**)malloc(sizeof(particle*)*num);
  int count = 0;
  while(*fgets(buff, 255, (FILE*)in)!= EOF)
  {
    sys[count] = new_particle(buff);
  }
};
//output results to python for plotting
void outputVis();
