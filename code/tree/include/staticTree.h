#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#ifndef STATICTREE
#define STATICTREE


  typedef struct node node;
  #define NUM 4

  //struct for individual node
  struct node
  {
    node* children;
    double COM[2];
    double mu;
    particle* particle;
  };
  //struct for tree
  typedef struct
  {
    //head node
    node* head;
    double dim;
    //comparison function pointerf
  } staticTree;
  //node constructor
  //static float G= 6.674e-11;  //mks gravitational constant
  //static float pi= 3.141592653;//maximum precision pi for 4B floating point
  //static float theta= 0.5;
  extern node* new_Node();
  extern node* addChildren(node* this);
  extern double* updateCOM(node* curr);
  extern void tree_calculateForce(node* curr, particle* this, double bound, double theta);
  extern void tree_reset(staticTree* this);
  extern void freeTree(staticTree* this);
  //Tree Printer
  extern void printTree(node* this, int level);
  extern void preorder(void* (*func)(node* root, void* val));
  //tree constructor
  extern staticTree* new_StaticTree(short num);
  //inserts node in tree
  extern void insertParticle(node* incumbant, particle* insertion, double bound, double centerx, double centerz);
  //compare 2 nodes using an external function

#endif
