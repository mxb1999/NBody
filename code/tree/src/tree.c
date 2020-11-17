#include "staticTree.h"
//node constructor
node* new_Node()
{
  node* this = (node*)malloc(sizeof(node));
  if(!this)
  {
    //printf("%s\n", "Hello");
    return NULL;
  }
  //printf("New Node: %p\n", this);
  this->COM[0] = 0;
  this->COM[1] = 0;
  this->children = NULL;
  this->mu = 0;
  this->particle = NULL;
  //printf("children: %p\n", this->children);
  return this;
};

node* addChildren(node* this)
{
  this->children = (node*)malloc(sizeof(node)*NUM);
  if(this != NULL)
  {
    for(int i = 0;i < NUM;i++)
    {
      this->children[i].COM[0] = 0;
      this->children[i].COM[1] = 0;
      this->children[i].children = NULL;
      this->children[i].particle = NULL;
      this->children[i].mu = 0;
    }
    return this->children;
  }
  return NULL;
}

//tree constructor
staticTree* new_StaticTree(short num)
{
  staticTree* this = (staticTree*)malloc(sizeof(staticTree));
  if(!this)
  {
    return NULL;
  }
  this->head = new_Node();
  return this;
};
void printTree(node* this, int level)
{
  node* children = this->children;
  for(int i = 0; i < level; i++)
  {
    printf("%s", "   ");
  }
  printf("Node: %e :: ", this->mu);
  if(children == NULL)
  {
    printf("%p\n", this->particle);
    return;
  }
  for(int i = 0; i < NUM; i++)
  {
      printf("\n");
      printTree(&children[i], level+1);
  }

//printf(" || \n");

};
//update the COM location and reduced mass for each given node
double* updateCOM(node* curr)
{
  double* result = (double*)malloc(sizeof(double)*3);
  if(curr != NULL && curr->particle != NULL)
  {
    result[0] = curr->particle->pos[0];//x coordinate
    result[1] = curr->particle->pos[1];//z coordinate
    result[2] = curr->particle->mass;//mass
    curr->COM[0] = result[0];
    curr->COM[1] = result[1];
    curr->mu = result[2];
    return result;
  }
  if(curr == NULL || curr->children == NULL)
  {
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    return result;
  }
  double mSum = 0;//sum of the reduced masses
  double xm = 0;//sum of the x coordinate * the reduced mass for each child node
  double zm = 0;//sum of the z coordinate * the reduced mass for each child node
  double mProd = 1;//product of the masses
  //recursively call on each of the children and add to
  for(int i = 0; i < NUM;i++)
  {
    double* temp = updateCOM(&curr->children[i]);
    mSum += temp[2];
    xm += temp[2]*temp[0];
    zm += temp[2]*temp[1];
    free(temp);
  }
  //printf("%e %e %e\n", xm,zm,mProd/mSum);
  result[0] = xm/mSum;
  result[1] = zm/mSum;
  result[2] = mProd/mSum;
  curr->COM[0] = result[0];
  curr->COM[1] = result[1];
  curr->mu = mSum;
  return result;
};




//calculate the force on a given particle
void tree_calculateForce(node* curr, particle* this, double bound, double theta)
{
  //Essentially a postorder tree traversal
  //If the conditions are satisfied (particle in node, or reduced mass quantifier), then update the force params
  //Otherwise, recursively travel to other nodes
  particle* other = curr->particle;
  if(other == this)
  {
    return;
  }

  double dist = sqrt(pow(curr->COM[0]-this->pos[0],2) + pow(curr->COM[1]-this->pos[1],2));
  node* children = curr->children;
  if(other != NULL || bound/dist < theta)
  {
    double force = curr->mu*G/pow(dist,2);
  //  printf("Tree Force: %f\n", force);
    double fx = (curr->COM[0]-this->pos[0])/dist*force;
    double fz = (curr->COM[1]-this->pos[1])/dist*force;
    this->force[0] += fx;
    this->force[1] += fz;
    return;
  }else if(children != NULL)
  {
    for(int i = 0; i < NUM; i++)
    {
      tree_calculateForce(&children[i], this, bound/2,theta);
    }
  }


}




void freeNode(node* this)
{
  if(this == NULL)
  {
    return;
  }
  if(this->children != NULL)
  {
    node* children = this->children;
    for(int i = 0; i < NUM; i++)
    {
      freeNode(&children[i]);
    }
  }
  free(this->children);
}
void tree_reset(staticTree* this)
{
  if(this == NULL)
  {
    return;
  }
  node* children = this->head->children;
  if(children != NULL)
  {
    for(int i = 0; i < NUM; i++)
    {
      freeNode(&children[i]);
    }
  }

  this->head->particle = NULL;
};
void freeTree(staticTree* this)
{
  freeNode(this->head);
  free(this->head);
  free(this);
}

void insertParticle(node* target, particle* insertion, double bound, double centerx, double centerz)
{
  particle* curr = target->particle;
  node* children = target->children;
  if(curr == insertion)
  {
    return;
  }
  //if the target node has no particle and no children, add the particle and return
  if(curr == NULL && children == NULL)
  {
    target->particle = insertion;
    return;
  }
  double x = insertion->pos[0];
  double z = insertion->pos[1];
  int greaterX = (x > centerx);
  int greaterZ = (z > centerz);
  if((x > centerx + bound || z > centerz + bound) || (z < 0 || x < 0))
  {
   // printf("Brr %e %e %e\n", x,z, bound);
    return;
  }
  int loc = greaterX + 2*greaterZ;//unique zone identifier
  //if the target node has no particle and children, determine if the desired node is null, if so create a new one and place the particle there, otherwise recursively call insertParticle
  if(curr == NULL)
  {
  //  printf("%s\n", "Recurse 1" );
    insertParticle(&children[loc], insertion, bound/2, centerx+bound/4*(greaterX+-1*!greaterX), centerz+bound/4*(greaterZ+-1*!greaterZ));
    return;
  }
  //if the target node has a particle, copy the address and delete it from the target node. Then determine the zones for the 2 particles. If they are the same, then place the preexisting particle and recursively call. Otherwise place them in seperate nodes
  target->particle = NULL;
  addChildren(target);
  children = target->children;
  int greaterX2 = (curr->pos[0] >= centerx);
  int greaterZ2 = (curr->pos[1] >= centerz);
  int loc2 = greaterX2 + 2*greaterZ2;//unique zone identifier
  if(loc2 == loc)
  {
    insertParticle(&children[loc2], curr, bound/2, centerx+bound/4*(greaterX+-1*!greaterX), centerz+bound/4*(greaterZ+-1*!greaterZ));
    insertParticle(&children[loc], insertion, bound/2, centerx+bound/4*(greaterX+-1*!greaterX), centerz+bound/4*(greaterZ+-1*!greaterZ));
    return;
  }
  children[loc].particle = insertion;
  children[loc2].particle = curr;
}
/*
//inserts particle in tree
void insertParticle(node* incumbant, particle* insertion, double bound, double centerx, double centerz)
{
  if(incumbant == NULL)
  {
    printf("%s\n", "NULL");
    incumbant = new_Node();
    incumbant->particle = insertion;
    return;
  }
  //printf("%s\n", "Started");
  //if the node has children, decide the proper zone and recursively decide where to place the particle
  short cond3 = ((insertion->pos[0] < centerx));
  short cond4 = ((insertion->pos[1] < centerz));
  short loc = (insertion->pos[0] < centerx) + 2*(insertion->pos[1] < centerz);
  if(incumbant->children != NULL)
  {
    printf("%s\n", "Recurse");
    node* temp = incumbant->children[loc];
    //recursively call the function
    if(temp == NULL)
    {
      incumbant->children[loc] = new_Node();
      incumbant->children[loc]->particle = insertion;
    }else
    {
      insertParticle(incumbant->children[loc],insertion, bound/2, centerx+bound/4*(-1*cond3 + !cond3), centerz+bound/4*(-1*cond4 + !cond4));
    }
    return;
  }
  //if no particle is in the zone, replace and return
  if(incumbant->particle == NULL)
  {

    incumbant->particle = insertion;
    //printf("%s %p\n", "Inserted: ", incumbant);
    return;
  }
  //if the node has no children but has a particle, then this is a node dispute

  particle* curr = incumbant->particle;
  if(bound > 1)
  {
    ////printf("%f, %f\n", centerx+bound/4*-1*((curr->pos[0] < centerx)), centerz);
    ////printf("(%f, %f) (%f, %f)\n", curr->pos[0],curr->pos[1],insertion->pos[0],insertion->pos[1]);
  }
  if(curr->pos[0] == insertion->pos[0] && curr->pos[1] == insertion->pos[1])
  {
    //printf("%s\n", "Same particle");
    return;
  }
  addChildren(incumbant);  //add empty children to the node w/ reduced bounds
  incumbant->particle = NULL; //remove the reference to curr in the node
  //if the particles are at the same location, print warning and return
  //printf("%s\n", "Divided");
  short loc2 = (curr->pos[0] < centerx) + 2*(curr->pos[1] < centerz);

  ////printf("Incumbant: (%f,%f) Insertion: (%f,%f) %d  %d\n", curr->pos[0],curr->pos[1],insertion->pos[0],insertion->pos[1],loc,loc2);
  ////printf("%f\n", bound/2);
  //call insert particle for the current node's particle
  incumbant->children[loc2] = new_Node();
  incumbant->children[loc2]->particle = curr;

  if(loc != loc2)
  {
    incumbant->children[loc] = new_Node();
    incumbant->children[loc]->particle = insertion;
  }else
  {
    if(bound > 1)
      printf("%e %e %e :: (%e %e) :: (%e,%e)\n", bound, centerx, centerz, insertion->pos[0], insertion->pos[1], curr->pos[0],curr->pos[1]);
  //  printf("%s %f %f %f\n", "eh",insertion->pos[0], curr->pos[0], bound);
    insertParticle(incumbant->children[loc2],insertion, bound/2, centerx+bound/4*(-1*cond3 + !cond3), centerz+bound/4*(-1*cond4 + !cond4));
    //call insert particle for insertion, if there is a conflict in
  }

};
*/
