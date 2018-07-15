#include<iostream>
using namespace:: std;
void merge(int* src,int* help,int lo,int mid,int hi )
{
  if(src == NULL || help == NULL)
  {
    return;
  }
  int index = lo;
  int i = lo;
  int j = mid;
  while(i < mid && j < hi)
  {
    if( src[i] < src[j] )
    {
      help[index++] = src[i++];
    }
    else 
    {
      help[index++] = src[j++];
    }
  }
  while(i < mid)
  {
    help[index++] = src[i++];
  }
  while(j < hi)
  {
    help[index++] = src[j++];
  }
  for(i = lo; i < hi;i++)
  {
    src[i] = help[i];
  }
}
void mergeSortCore(int* src,int* help,int lo,int hi)
{
  //  至少有两个才能merge
  if(lo + 1 >= hi)
    return;
  int mid = lo + ((hi - lo) >> 1);

  mergeSortCore(src,help,lo,mid);
  mergeSortCore(src,help,mid,hi);
  merge(src,help,lo,mid,hi);
}
void mergeSortCore_ByLoop(int* src,int* help,int length)
{
  int lo = 0;
  int mid = 0;
  int hi = 0;
  int gap = 1;
  for(; gap < length; gap *= 2)
  {
    for(int i = 0; i < length; i += 2*gap)
    {
      lo = i;
      mid = lo + gap;
      hi = lo + 2 * gap;
      if(hi > length)
      {
        hi = length;
      }
      merge(src,help,lo,mid,hi);
    }
  }
}
void mergeSort(int* src,int length)
{
  if(src == NULL || length < 0)
    return;
  int* help = (int *) malloc(sizeof(int)*length);
  if(help == NULL)
  {
    printf("malloc\n");
    return;
  }
  mergeSortCore_ByLoop(src,help,length);
  free(help);
}

int main()
{
  //int array[] = { 5,4,3,2,1 };
  int array[] = { 5,3,4,2,1 };
  mergeSort(array,sizeof(array)/ sizeof(array[0]));
  for(auto i:array)
  {
    cout << i <<" ";
  }
  cout << endl;
  return 0;
}
