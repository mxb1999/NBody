#include "linkedlist.h"
lNode* new_lNode(void* val)//allocate space for and return a new node
{
  lNode* this = (lNode*)malloc(sizeof(lNode));
  if(this == NULL)//No room
  {
    printf("%s\n", "Could not allocate space for linkedlist");
    return NULL;
  }
  this->next = NULL;
  this->val = val;
  return this;
}
LinkedList* new_LinkedList()//create and return a pointer to a new linkedlist
{
  LinkedList* this = (LinkedList*)malloc(sizeof(LinkedList));
  if(this == NULL)//No room
  {
    printf("%s\n", "Could not allocate space for linkedlist");
    return NULL;
  }
  this->head = new_lNode(NULL);
  this->tail = this->head;
  this->size = 0;
  return this;
}
void insertVal(lNode* this, void* val)//insert a value into an existing node
{
  if(this == NULL)
  {
    return NULL;
  }
  this->val = val;
}

void* getVal(lNode* this)//return the pointer to the value stored by the node
{
  if(this == NULL)
  {
    return NULL;
  }
  return this->val;
}
void append(LinkedList* this, void* val);
{
  if(this == NULL)
  {
    return;
  }
  lNode* nova = new_lNode(val);
  this->tail->next = nova;
  this->tail = nova;
  this->size++;
}
LinkedListIterator* new_LinkedListIterator(LinkedList* tgt)//create and return a pointer to a new linkedlistIterator
{
  LinkedListIterator* this = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));
  if(this == NULL || tgt == NULL)//No room
  {
    printf("%s\n", "Could not allocate space for linkedlist");
    return NULL;
  }
  this->curr = tgt->head;
  this->host = tgt;
  return this;
}
lNode* iterator_next(LinkedListIterator* this)//return the current node pointed to by the iterator and shifts to the next link in the chain
{
  if(this == NULL || this->curr->next == NULL)
  {
    return NULL;
  }
  lNode* result = this->curr;
  this->curr = this->curr->next;
  return result;
}
int getSize(LinkedList* this)
{
  if(this == NULL)
  {
    return;
  }
  return this->size;
}
void freeNode(lNode* this)//memory deallocation propogates down chain
{
  if(this == NULL)
  {
    return;
  }
  freeNode(this->next);
  free(this);
};
void freeList(LinkedListIterator* this, int freeNodes)
{
  if(this == NULL)
  {
    return;
  }
  if(freeNodes)
  {
    freeNode(this->head);
  }
  free(this);
};
