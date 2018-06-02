#include<iostream>
#include<vector>
using namespace::std;
#define swap(a,b) int tmp = a;a = b; b = tmp
int partition(vector<int> &v,int lo,int hi)
{
  if( lo >= hi  )
  return lo;
  int key = v[lo];
  while(lo < hi )
  {
    while( lo < hi && v[hi] > key )
    {
      hi--;
    }
    while( lo < hi && v[lo] < key )
    {
      lo ++;
    }
    swap(v[lo],v[hi]);
  }
    swap(v[lo],key);
    return lo;
}

void  GetLeastNumebrs(vector<int> &v,int k)
{
  int i = 0;
  int start = 0;
  int end = v.size() -1;
  int index = partition(v,start,end);
  // 1 2 3 4 5 6 7   前4大元素是1234 下标是从3开始
  while(index != k  -1)
  {
    cout << "index:" << index<< endl;
    for( i = 0; i < (int)v.size(); i++ )
    {
      cout << v[i] << endl;
    }
    if(index > k - 1)
    {

      end = index - 1;
    }
    else if( index < k - 1 )
    {
      start = index + 1;
    }
    index = partition(v,start,end);
  }
  cout << " final result " << endl;
  for(i = 0; i <= index ; i++ )
  {
    cout << v[i] << endl;
  }
  cout << endl;
}
int main()
{
  vector<int> v = {5,4,3,2,1};
  GetLeastNumebrs(v,3);
  return 0;
}
