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
//tree constructor
staticTree* new_StaticTree(int (*compareTo)(void* a, void* b), void* headVal, short num)
{
  staticTree* this = (staticTree*)malloc(sizeof(staticTree));
  if(!this)
  {
    return NULL;
  }
  this->head = new_Node(headVal);
  this->compareTo = compareTo;
  numNodes = num;
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
int insertNode(void* val, staticTree* this)
{
  if(this == NULL)
  {
    printf("%s\n", "Hello");

    return -1;
  }
  node* head = this->head;
  int insertion = this->compareTo(this->head->val, val);
  if(head->children[insertion] != NULL)
  {

    printf("%p\n", head->children+insertion);
    return insertNode(val, new_StaticTree(this->compareTo, this->head->val, numNodes));
  }
  head->children[insertion] = new_Node(val);
  printf("%s\n", "GOODBYE");
  return 0;
};
