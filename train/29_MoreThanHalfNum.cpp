#include<iostream>
#include<vector>
using namespace::std;
int partition(vector<int>v,int lo,int hi)
{
  // 5  4 
  // lo == hi return lo
  if(lo <= hi)
    return lo;
  int key = v[lo];
  while(lo < hi )
  {
    if( lo < hi  && v[hi] > key )
    {
      hi--;
    }
    if( lo < hi && v[lo] < key )
    {
      lo++;
    }
    //swap
  }
  //swap
  return lo;
}
int MoreThanHalfNum_2(vector<int> v)
{
 int start = 0;
 int end = v.size() - 1;
 int mid = start  + (end- start) / 2;
 int ret = partition(v,start,end);
 while(ret !=  mid)
 {
    if( ret < mid )
    {
      start = ret +1;
      ret  = partition(v,start,end); 
    }
    else 
    {
      end = ret  - 1;
      ret = partition(v,start,end);
    }
 }
 return v[ret];
}
int MoreThanHalfNum(const vector<int> v)
{
  int number = v[0];
  int times = 1;
  auto iter = v.begin() + 1;
  for(; iter != v.end(); iter++)
  {
    if( *iter != number) 
    {
      times --;
      if( times == 0 )
      {
        number = *iter;
        times = 1;
      }
    }
    else if( *iter == number )
      times++;
  }
  return number;
}
int main()
{
  vector<int> v = { 0,4,5,2,2,2,2,3 };
  cout << MoreThanHalfNum(v);
}
