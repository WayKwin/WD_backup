#include<iostream>
using  namespace::std;
const int MAX = 10000;
int main()
{
  int arr[MAX] = {0};
  int i = 2;
  for(; i * i < MAX;i++)
  {
    if(arr[i] == 1)
      continue;
    int j = 2*i;
    for(; j  < MAX; j+=j )
    {
      arr[j] = 1;
    }
  }
  for(i = 2; i < MAX; i++)
  {
    if(arr[i] == 0)
      printf("%d  ",i);
  }
  printf("\n");
}

