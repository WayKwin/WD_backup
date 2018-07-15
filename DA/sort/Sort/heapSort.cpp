#include<iostream>
using namespace::std;

void Sink(int *a,int begin,int end)
{
  while(2*begin+ 1 < end)
  {
    int child = 2*begin + 1; 
    if(child + 1 < end && a[child] < a[child + 1])
      child += 1;
    if(a[child] > a[begin])
      swap(a[child],a[begin]);
    else 
      break;
    begin = child;
  }
}
void BuildHeap(int *a,int length)
{
  // 0 1 2
  int i = length /2 ;
  while(i > 0)
  {
    Sink(a,i,length);
    i--;
  }
}
void HeapSort(int *a,int length)
{
  BuildHeap(a,length);
  int i = length - 1;
  while(i > 0)
  {
    swap(a[0],a[i]);
    Sink(a,0,i);
    i--;
  }
}
int main()
{
  //int array[] = {5,4,3,2,1};
  int array[] = {4,3};
  HeapSort(array,sizeof(array)/sizeof(array[0]));
  for(auto i : array)
  {
    cout << i << " ";
  }
  return 0;
}
