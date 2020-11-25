#include <stdio.h>
#include <stdlib.h>
#ifndef LLIST
#define LLIST
  //Bog standard linkedlist implementation, nothing much to see here
  typedef struct lNode lNode;

  struct lNode
  {
      lNode* next;
      void* data;
  };
  typedef struct
  {
    lNode* head;
    lNode* tail;
    int size;//slightly more effort to update, but useful for quadtree implementation
  }LinkedList;

  extern void freeNode(lNode* this);
  extern LinkedList* new_LinkedList();//create and return a pointer to a new linkedlist w/ null values
  extern LinkedList* new_LinkedList(void* val);//create and return a pointer to a new linkedlist w/ a given value
  extern void insertVal(lNode* this, void* val);//insert a value into an existing node
  extern lNode* new_lNode(void* val);//allocate space for and return a new node
  extern void* getVal(lNode* this);//return the pointer to the value stored by the node
  extern void append(LinkedList* this,void* val);
  extern int getSize(int i);
  extern void freeList(LinkedListIterator* this, int freeNodes);
  typedef struct
  {
    lNode* curr;
    LinkedList* host;
  }LinkedListIterator;//expediant for iterating along the length of a linkedlist without changing its values
  extern LinkedListIterator* new_LinkedListIterator();//create and return a pointer to a new linkedlistIterator
  extern lNode* iterator_next(LinkedListIterator* this);//return the current node pointed to by the iterator
#endif
