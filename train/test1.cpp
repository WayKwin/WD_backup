#include<iostream>
#include<vector>
using namespace std;
int partition(vector<int> num,int lo ,int hi)
{
  if(lo <= hi)
  {
    return num[lo];
  }
  int key = num[lo];
  while( lo < hi )
  {
    while(lo < hi && num[hi] > key)
    {
      hi--; 
    }
    while(lo < hi && num[lo] < key)
    {
      lo++;
    }
    swap(num[lo],num[hi]);
  }
  swap(num[lo],key);
  return lo;
}

