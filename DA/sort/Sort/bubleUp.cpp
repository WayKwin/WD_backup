#include<iostream>
using namespace::std;
void BubleUp(int *a,int length)
{
  if(a == NULL || length <= 0)
  {
    return;
  }
  bool IsSort = false;
  int size = length;
  for(; IsSort = !IsSort; size--)
  {
    for(int i = 0; i < size - 1; i++)
    {
        if(a[i] >a[i+ 1])
        {
          swap(a[i],a[i+1]);
          IsSort = false;
        }
    }
  }
}
int main()
{
  //int a[] = {4,3,2,1};
  int a[] = {4,2,3,1};
  BubleUp(a,sizeof(a)/sizeof(a[0]));
  for(auto i : a)
  {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
