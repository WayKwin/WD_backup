#include<iostream>
using namespace::std;
void selcetion(int *a,int length)
{
  int i = 0;
  int j = 0;
  int Min;
  for(; i < length; i++)
  {
    Min = i; 
    for(j = i + 1; j < length;j++)
    {
      if(a[j] < a[i]) 
      {
        Min = j;
        break;
      }
    }
    if(Min == i)
    {
      //printf("不能说明有序了");
    }
      swap(a[i],a[Min]);
  }
}
int main()
{
  //int a[] = {4,2,3,1};
  //int a[] = {4,3,2,1};
  int a[] = {1,3,2,4};
  selcetion(a,sizeof(a)/sizeof(a[0]));
  for(auto i : a)
  {
    cout << i << " ";
  }
  cout << endl;
  return 0;
  
}
