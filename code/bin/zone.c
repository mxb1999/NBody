#include "sim.h"


extern zone* newZone(float x, float z, , float b,float m)
{
  zone* this = (zone*)malloc(sizeof(zone));
  if(this == NULL)
  {
    return NULL;
  }
  this->center = *newVector2(x, z);
  this->COM = *newVector2(x,z);
  this->centerV = *newVector2(0,0);
  this->bound = b;
  this->mass = m;
  return this;
};//constructor function for zones
//external accessor functions
extern float zone_getX(zone* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->center.x;
};
extern float zone_getZ(zone* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->center.z;
};
extern float zone_getVX(zone* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->centerV.x;
};
extern float zone_getVZ(zone* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->centerV.z;
};
extern float zone_bound(zone* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->bound;
};
extern float zone_massTotal(zone* this)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->mass;
};


//functions to adjust zone value

//
/*Grid placement scheme
______________________
|          |          |
|    1     |    0     |
|__________|__________|
|          |          |
|    3     |    2     |
|__________|__________|_
*/
extern void divideZone(node* inPlace, zone* insert)//If an insertion tries to place a particle in an occupied zone
{
  if(this == NULL || this->val == NULL)
  {
    return;
  }
  //declare a new zone and allocate memory for children pointers
  zone* zone = (zone*)inPlace->val;
  node** children = addChildren(inPlace);
  //get particle/zone parameters
  //params of incumbent zone
  float x = zone->center.x;
  float z = zone->center.x;
  //params of inserted zone
  float xi = insert->center.x;
  float massi = insert->mass;
  float zi = insert->center.z;
  //if the particle locations are the same
  if(x == xi && z == zi)
  {
    printf("%s\n", "Cannot insert duplicate particles");
    return;
  }
  short place1 = (x < comX)+2*(z < comZ);
  short place2 = (xi < comX)+2*(zi < comZ);
  if(place1 == place2)
  {
    children[place1] = new_Node(newZone(x,z,b/2,mass));
    for(int i = 0; i < numbranch;i++)
    {
      if(i != place1)
      {
        children[i] = children[i] = new_Node(NULL);
      }
    }
    divideZone(children[place1], insert);
  }else
  {
    for(int i = 0; i < numbranch;i++)
    {
      if(i == place1)
      {
        children[i] = new_Node(newZone(x,z,zone->bound/2,mass));
      }else if(i == place2)
      {
        children[i] = new_Node(newZone(xi,zi,zone->bound/2,massi));
      }else
      {
        children[i] = new_Node(NULL);
      }
    }
  }
};
extern zone* readInBH(char* fileName)
{
  if(this == NULL)
  {
    return -1;
  }
  return this->center.x;
};//read input parameters from a given filename
