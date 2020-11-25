#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Performs statistical analysis on a given set of data
/*
  Desired Functions:
    -Mean
    -Median
    -Mode
    -Standard Deviation
    -Weighted Mean
    -sort (probably quicksort cuz why not)
*/
double average()
{
  double sum;
  for(int i = 0; i < size; i++)
  {
    sum += target[i];
  }
  return sum/size;
}
double stddev()
{

}
double weightedMean(double* target, int size, double dev, double avg)
{
  double weightSum = 0;
  double prodSum = 0;
  double temp;
  for(int i = 0; i < size; i++)
  {
    temp = target[i];
    double weight = 1/pow(dev - (avg-temp),2);
    weightProd += temp*weight;
    weightSum += weight;
  }
  return weightProd/weightSum;
}
#define LOWBOUND 10
//quicksort algorithm w/ last number as pivot
void quicksort(double* target, int low, int high)
{

  if(high - low <= 1)
  {
    return;
  }
  //select pivot
  int pivloc = high;
  double pivot = target[high];//more efficient division, bit shifted by 1
  //compare each element with pivot. If greater than the pivot, then swap
  for(int i = 0;i < pivloc; i++)
  {
    double x = target[i];
    double y = target[pivloc-1];
    if(x > pivot)
    {

      target[i] = y;
      target[pivloc] = x;

      target[--pivloc] = pivot;
      if(y > pivot)
      {
        i--;
      }
    }
  }
  quicksort(target, low,pivloc-1);
  quicksort(target, pivloc+1, high);
}
int main(int argc, char const *argv[]) {
  double test[] = {4.3,76.12,2.3,97.312,200.0,-34.32,1.12};
  quicksort(test, 0, 6);
  for(int i = 0; i < 7;i++)
  {
    printf("%f\n", test[i]);
  }
  return 0;
}
