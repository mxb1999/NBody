#include <stdio.h>
#include <stdlib.h>
#ifndef STATICTREE
typedef struct node node;
int numNodes;
//struct for individual node
struct node
{
  node** children;
  void* val;
};
//struct for tree
typedef struct
{
  //head node
  node* head;
  //comparison function pointerf
  int (*compareTo)(void* a, void* b);
} staticTree;
//node constructor
node* new_Node(void* val);
//Tree Printer
void printTree(node* this);
//tree constructor
staticTree* new_StaticTree(int (*compareTo)(void* a, void* b), void* headVal, short num);
//inserts node in tree
int insertNode( void* val,staticTree* this);
//compare 2 nodes using an external function
int compare(node* a, node* b);
#endif
