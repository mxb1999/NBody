#include "polytree.h"

node* newNode(float* coor, float m, float rad)
{
  node* node = (node*)malloc(sizeof(node));
  if(!this)
  {
    return NULL;
  }
  this->m = m;
  this->coor = coor;
  this->children  = (node*)malloc(branches*sizeof(node));
  this->rad = rad;
  return this;
}
polytree* newTree(int num, float* coor, float m, float rad)
{
  polytree* this = (polytree*)malloc(sizeof(polytree));
  if(!this)
  {
    return;
  }
  this->
}
//insert a node
//bounds formatted as 2d flattened array: 1st dim is the dimension, 2nd dim is upper/lower bound
int addNode(node* this, float* coor, float* bounds, int dim, float m)
{
  if(!this || !target)
  {
    return -1;
  }
  //represent state as single binary string: 0 = below median, 1 = above
  short state = 0;
  float* newbounds = (float*)calloc(sizeof(float)*dim);
  for(int i = 0; i < dim; i++)
  {
    //will end up a number 1->4 depending on location and bounds
    state += 1<<i * (coor[i] > medCoor);
    //gets 1/2 the bounds
    float diff = (bounds[i*2 + 1]-bounds[i*2])/2;
    //determine whether the offset will be needed, upper or lower half of quadrant
    float offset = state >> i * diff;
    newbounds[i] = bounds[i*2]+offset;
    newbounds[i+1] = newbounds[i] + diff + offset;
  }
  addChild(this, target, state, coor, bounds, dim,m);
  return 0;
};
void addChild(node* this, int state, float* coor, float* bounds, int dim, float m)
{
  if(!this || !target)
  {
    return;
  }
  node* child = this->children[state];
  if(child != NULL)
  {
    addNode(child, coor, target, bounds, dim)
    return;
  }
  int sum = 0;
  for(int i = 0; i < dim; i++)
  {
    sum+= pow(coor[i]-child->coor[i],2);
  }
  child = newNode(coor, m, sqrt(sum));
  this->m += m;
}
//print the tree
void printTree(polytree* this)
{

};
//general purpose postorder tree traversal for updating nodes with various functions
void postorderApply(polytree* this, double (*func)(node*))
{

};
