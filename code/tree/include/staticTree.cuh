#include <cuda_runtime.h>
#include "staticTree.h"
#ifndef STATICTREECUDA
#define STATICTREECUDA

  //node constructor
  //static float G= 6.674e-11;  //mks gravitational constant
  //static float pi= 3.141592653;//maximum precision pi for 4B floating point
  //static float theta= 0.5;
  extern __device__ node* new_Node();
  extern __device__ node* addChildren(node* this);
  extern __device__ double* updateCOM(node* curr);
  extern __device__ void tree_calculateForce(node* curr, particle* this, double bound);
  extern __device__ void tree_reset(staticTree* this);
  extern __device__ void freeTree(staticTree* this);
  //Tree Printer
  extern void printTree(node* this, int level);
  extern void preorder(void* (*func)(node* root, void* val));
  //tree constructor
  extern staticTree* new_StaticTree(short num);
  //inserts node in tree
  extern void insertParticle(node* incumbant, particle* insertion, double bound, double centerx, double centerz);
  //compare 2 nodes using an external function

#endif
