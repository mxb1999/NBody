#include <stdio.h>
#include <stdlib.h>
#include <cmath.h>
#ifndef POLYTREE
#typedef struct node node
//Struct value containers for each node
int branches = 4;
struct node
{
  node* children;
  float* coor;
  float m;
  int last;

  float rad;
};
//struct definition for overall tree
#typedef struct
{
  node* head;
} polytree;
//insert a node
int addNode(polytree* this, int* coor);
//print the tree
void printTree(polytree* this);
//general purpose postorder tree traversal for updating nodes with various functions
void postorderApply(polytree* this, double (*func)(node*));

#endif
