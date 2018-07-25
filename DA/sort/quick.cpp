#include<iostream>
//#include<
using namespace std;

int partation(int *a,int lo,int hi)
{

  if(lo + 1 >= hi)
  {
    return lo;
  }
  hi--;
  int key = a[lo];
  while(1)
  {
    while(lo < hi && a[hi] < key )
  }

}
