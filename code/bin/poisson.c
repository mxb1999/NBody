#include "poisson.h"

//Structure of Poisson Sim:
/*
  1. Call Init() -> initializes FFTW plan, initializes mesh with establishMesh and calls main_loop(). After main_loop execution, output results and submit for user input. If user has no further tasks,
  delete fftw plan and return.

*/
void establishMesh(double* mesh,particle* system, int num, int zones, double dim)
{
  double del = dim/zones;
  int x,z;
  for(int i = 0; i < num; i++)
  {
    x = (int)(system[i].pos[0])/del;
    z = (int)(system[i].pos[1])/del;
    mesh[x*dim + z] += system[i].mass*(G*4*PI)/(del*del);
  }
  for(int j = 0; j < num; j++)
  {
      for(int m = 0; m < num; m++)
      {
        
      }
  }
};
void mainLoop(fftw_complex* sol, fftw_plan p, particle* system,double* mesh, int numP, int dim, double size, double time, int step)
{
  for(int i = 0; i < step; i++)
  {
    establishMesh(mesh, system, numP,dim, size);
    //calculate Potential
    fftw_execute(p);
    //calculate
    

  }

};
void init(particle* system,int numParticles, int num, double dim, double time, int step)
{
  double* in  = (double*)malloc(sizeof(double)*dim*dim);
  if(in == NULL)
  {
    printf("%s\n", "Could not allocate mesh, insufficient available memory");
    return NULL;
  }
  fftw_complex* out;
  fftw_plan p;
  out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*dim*dim);
  p = fftw_plan_dft_r2c_2d(dim,dim,in,out,FFTW_FORWARD,FFTW_MEASURE);
  mainLoop(out,p,system, in, numParticles, num, dim, time, step);

};
double* poisson_field(double* potential, int num, double dim)
{

};
