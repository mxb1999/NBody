//force calculation based on Barnes-Hut paper method
//for each particle p: start at the root: if l is the length of the cell being processed and D is the distance from the COM of the cell to p
//if l/D < theta(accuracy param), then use the COM of the cell to calculate the net force of that segment of the tree on p, otherwise recursively go to the children of that zone
#include "sim.h"
//#define N 1e4
#define RANDF (float)rand()/((float)RAND_MAX)
#define OOB(x,z,u,l) ((x > u || x < l) || (z > u || z < l))
void tree_timeLoop(double time, double step, particle** sys, char* out, int num, double bound, double theta)//main time loop for the simulation
{
  FILE* file = fopen(out, "wb");//open file for results
  //FILE* file2 = fopen(out, "w");//open file for results

  double t = 0.0;
  int stepNum = (int)(time/step);
  fwrite(&bound,sizeof(double),1, file);
  fwrite(&num,sizeof(int),1, file);
  fwrite(&stepNum,sizeof(int),1, file);
  int c = 0;
  int d = 0;
  //int track[N]={0};
  while(t <= time)
  {
    staticTree* bh = new_StaticTree(4);
    for(int i = 0; i < num; i++)
    {
      insertParticle(bh->head, sys[i],bound,bound/2, bound/2);
    }

    //printf("%s\n", "Finished Insertion");
    updateCOM(bh->head);
    for(int i = 0; i < num; i++)
    {
        tree_calculateForce(bh->head, sys[i], bound, theta);
    }
    for(int i = 0; i < num; i++)
    {
        particle* this = sys[i];
        this->v[0] += this->force[0]*step;
        this->v[1] += this->force[1]*step;
        this->pos[0] += this->v[0]*step;
        this->pos[1] += this->v[1]*step;
        this->force[0] = 0;
        this->force[1] = 0;
        //printf("pos (%e, %e) \n", this->pos[0], this->pos[1]);//sqrt(pow(force[0],2)+pow(force[1],2)));

        //printf("%e %e\n", this->v[0]*step, this->v[1]*step);
       /* if(this->pos[0] < 0)
        {
          this->pos[0] = bound;
        }
        if(this->pos[0] > bound)
        {
          this->pos[0] = 0;
        }
        if(this->pos[1] < 0)
        {
          this->pos[1] = bound;
        }
        if(this->pos[1] > bound)
        {
          this->pos[1] = 0;
        }
        */
        //  printf("pos %f\n", this->pos[0]);//sqrt(pow(force[0],2)+pow(force[1],2)));
        fwrite(&this->pos[0],sizeof(double),1, file);
        fwrite(&this->pos[1],sizeof(double),1, file);
      
      
    }

    t+=step;
    if(((float)c)/stepNum*100 > d)
    {
     // printf("%d%c complete\n", d,'%');
      d++;
    }
    freeTree(bh);
    c++;
  }

  fclose(file);
  //printf("%s\n", "Tree Done");
  //
}

void brute_timeLoop(double time, double step, particle** sys, char* out, int num, double bound)
{
  FILE* file = fopen(out, "wb");//open file for results
  double t = 0.0;
  staticTree* bh = new_StaticTree(4);
  int stepNum = (int)(time/step);
  fwrite(&bound,sizeof(double),1, file);
  fwrite(&num,sizeof(int),1, file);
  fwrite(&stepNum,sizeof(int),1, file);
  int c = 0;
  int d = 0;
  while(t <= time)
  {
    //printf("%s\n", "Finished Insertion");
    updateCOM(bh->head);

    for(int i = 0; i < num; i++)
    {
      particle* this = sys[i];

      for(int j = 0; j < num; j++)
      {
        if(i!=j)
        {
          particle* tgt = sys[j];
          double dist = sqrt(pow(tgt->pos[0]-this->pos[0],2) + pow(tgt->pos[1]-this->pos[1],2));
          double f = -1*tgt->mass*this->mass*G/pow(dist,2);

          this->force[0] += (this->pos[0]-tgt->pos[0])/dist*f;
          this->force[1] += (this->pos[1]-tgt->pos[1])/dist*f;
        //  printf("Brute: %f\n", f);

        }

      }
  //    printf("Brute: (%f, %f)\n", this->force[0], this->force[1]);


    }
    for(int i = 0; i < num; i++)
    {
      particle* this = sys[i];
      this->v[0] += this->force[0]/this->mass*step;
      this->v[1] += this->force[1]/this->mass*step;
      this->pos[0] += this->v[0]*step;
      this->pos[1] += this->v[1]*step;
      this->force[0] = 0;
      this->force[1] = 0;
    //  printf("%f\n", this->pos[0]);
      fwrite(&this->pos[0],sizeof(double),1, file);
      fwrite(&this->pos[1],sizeof(double),1, file);
    }
    t+=step;
    if(((float)c)/stepNum*100 > d)
    {
      //printf("%d%c complete\n", d,'%');
      d++;
    }
    tree_reset(bh);
    c++;
  }
  fclose(file);
  //
}

#define REST 1
#define TREE 0
#define COMP pos[1]
/*
int main(int argc, char const* argv[])
{
  float bound = 10.0;
  particle* test1 = new_particle(1,2,0,0,10);
  particle* test2 = new_particle(2,3,0,0,10);
  particle* test3 = new_particle(2,2,0,0,10);
  particle* test4 = new_particle(1,4,0,0,10);
  staticTree* this = new_StaticTree(4);
  insertParticle(this->head, test1, bound, bound/2, bound/2);
  insertParticle(this->head, test2, bound, bound/2, bound/2);
  insertParticle(this->head, test3, bound, bound/2, bound/2);
  insertParticle(this->head, test4, bound, bound/2, bound/2);
  printTree(this->head, 0);
}
*/

int main(int argc, char const *argv[]) {

  //double* tree_force = (double*)malloc(sizeof(double)*N*2);//array to store force
  //double* poisson_force = (double*)malloc(sizeof(double)*N*2);
  //double* brute_force = (double*)malloc(sizeof(double)*N*2);
  double bound = 1e10;//length of test area in m
  double abound = 2e12;//length of test area in m
  double vbound = 1e4;//m/s initial velocity
  double mbound = 1e25;//average mass for gaussian bell curve
 
  /*particle* a = new_particle(bound/4, bound/4, 0, 0, mbound);
  particle* b = new_particle(bound*3/4, bound*3/4+bound/8, 0, 0, mbound);
  particle* c = new_particle(bound*3/4, bound*3/4-bound/8, 0, 0, mbound);
  particle* d = new_particle(bound/4, bound/4, 0, 0, mbound);
  particle* e = new_particle(bound*3/4, bound*3/4+bound/8, 0, 0, mbound);
  particle* f = new_particle(bound*3/4, bound*3/4-bound/8, 0, 0, mbound);
  sysTree[0] = a;
  sysTree[1] = b;
  sysTree[2] = c;
  sysBrute[0] = d;
  sysBrute[1] = e;
  sysBrute[2] = f;
*/
  int N=1e3;
  
    double theta = 0;
    for(float s = 0; s < 20;s+=1)
    {
      double avgTX = 0;
      double avgTZ = 0;

     // if(s != 0)
     // {
     //   N*=s;
     // }
      for(int q = 0; q < 10;q++)
      {  
      particle** sysBrute = (particle**)malloc(sizeof(particle*)*N);
      particle** sysTree = (particle**)malloc(sizeof(particle*)*N);
      for(int i = 0; i < N;i++)
      {
        int isnegvx = -1*rand()%2;
        int isnegvz = -1*rand()%2;

        double x = bound*RANDF+abound/2;
        
        double z = bound*RANDF+abound/2;

        double vx = REST*isnegvx*vbound*RANDF;
        double vz = REST*isnegvz*vbound*RANDF;
        double mass = mbound;//mbound*RANDF;
        sysTree[i] = new_particle(x, z, vx, vz, mass);
        sysBrute[i] = new_particle(x, z, vx, vz, mass);
      }
        clock_t start,mid, end;
        start = clock();
        tree_timeLoop(1, 1, sysTree, "treeResults.txt", N,abound,theta);//main time loop for the simulation
        mid = clock();
        brute_timeLoop(1, 1, sysBrute, "newtonianResults.txt", N,abound);//main time loop for the simulation
        end = clock();
        printf("Times: %e %e\n", ((double) (mid-start)) / CLOCKS_PER_SEC,((double) (end-mid)) / CLOCKS_PER_SEC);
        //double* statComp = (double*)malloc(sizeof(double)*N);
        double avgx = 0;
        double avgz = 0;
        //double* diff = malloc(sizeof(double)* N*2);
        for(int i = 0; i < N; i++)
        {
          particle* t = sysTree[i];
          particle* b = sysBrute[i];
          avgx += t->pos[0]-b->pos[0];
          avgz += t->pos[1]-b->pos[1];
          free(t);
          free(b);
        }
        avgTX = avgx/N;
        avgTZ = avgz/N;
        free(sysTree);
        free(sysBrute);
        }
      printf("Ree %e %e %d\n", (avgTX/(10))*100,(avgTZ/(10))*100, N);
      printf("\n");
     // N/=(s + (s==0));
      theta+=s/10;
    }
  

   
  return 0;
}
