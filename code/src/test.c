#include "staticTree.h"
#include "brute.h"
float G = 6.67408e-11;  //mks gravitational constant
float pi = 3.14159274101257324;//maximum precision pi for 4B floating point
int comparison(void* a, void* b)
{
  if(*(int*)a > *(int*)b)
  {
    return 1;
  }
  return 0;
}
int main(int argc, char const *argv[]) {

  int a = 5;
  int b = 4;
  staticTree* tester = new_StaticTree(&comparison, &a, 2);
  printTree(tester->head);
  insertNode(&b, tester);
  printTree(tester->head);

  return 0;
}
