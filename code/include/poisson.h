#include <math.h>
#include <fftw3.h>
#include <stdio.h>
#include "particle.h"
#ifndef POISSON
#define POISSON
  #define arr(i,j,dim) i*dim+j
  typedef struct
  {
    fftw_plan this_plan;
    fftw_complex* transform;
    double* grid;
    double bound;
    int dim;
  } mesh;
  extern mesh* new_mesh(int size, particle** sys, double bound);
  extern void establishMesh();
  extern void fftCalc(double* in, particle* system, int num, double dim);
  extern void poisson_field(double* potential, int num, double dim);
  /*
    Defining functions and variables necessary for solving the poisson equation
     - define f(x,y) as the mass density of each grid location
     - poisson equation is equal to G*4*pi*rho, sample rho at each location and fourier transform
     - establish and plot particles within mesh
     - Find force on each particle using the gravitational potential




  */
#endif
