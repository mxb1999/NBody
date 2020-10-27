#include <stdio.h>
#include <stdlib.h>
#include "simConst.h"
#ifndef BRUTE
#define BRUTE
  //solve by finding gravitational force on each particle due to every other particle
  //accept input as text file formatted w/ coordinates & velocities
  //Lack of COM abstraction -> 24 B per particle using floats

  typedef struct
  {
    //position coordinates
    float x;
    float y;
    //particle velocity
    float vx;
    float vy;
    //mass of the particle
    float mass;
  } particle;

  extern char* fileIn;
  extern particle** sys;
  extern float totalTime;
  extern float time;
  extern int num;
  extern float dt;
  //Constants

  //read and update arrays with initial information
  void readFile();
  //output results to python for plotting
  void outputVis();
  //update the movement of each particle based upon the forces acting on it
  void updateMovement();
#endif
