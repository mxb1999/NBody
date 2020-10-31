#include "staticTree.h"

//node constructor
node* new_Node(void* val)
{
  node* this = (node*)malloc(sizeof(node));
  if(!this)
  {
    return NULL;
  }
  this->children = (node**)calloc(sizeof(node*),numNodes);
  this->val = val;
  return this;
};
node* emptyNode()
{
  node* this = (node*)malloc(sizeof(node));
  if(!this)
  {
    return NULL;
  }
  this->children = (node**)calloc(sizeof(node*),numNodes);
  this->val = NULL;
  return this;
}
//tree constructor
staticTree* new_StaticTree(int (*comparison)(node* a, node* b), void* headVal, short num, int (*dispute)(node* i, node* a, node* b))
{
  staticTree* this = (staticTree*)malloc(sizeof(staticTree));
  if(!this)
  {
    return NULL;
  }
  this->head = new_Node(headVal);
  compareTo = comparison;
  numNodes = num;
  leafDispute = dispute;
  return this;
};
void printTree(node* this)
{
  node** children = this->children;
  printf("%p", this);
  for(int i = 0; i < numNodes; i++)
  {

    if(children[i] != NULL)
    {
      printTree(children[i]);
      printf("    " );
    }

  }

printf(" || \n");

};

//inserts node in tree
void insertNode(node* insert, node* target)
{
  //if the node is null -> replace node
  if(target == NULL)
  {
    target = insert;
    return;
  }
  //-1 indicates leaf, 0-numbranch indicates quadrant to examine
  int placement = compareTo(insert, target);
  //if the node is an internal node - > continue recursive descent
  if(placement != -1)
  {
    insertNode(insert, target->children[placement]);
  }
  //if the node is a leaf -> make new children and adjust accordingly.
  //How to structure new comparison?

  leafDispute(target, insert);

};
