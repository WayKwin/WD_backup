#include<iostream>
using namespace::std;
void insertion(int *a,int length)
{
  if(a == NULL || length < 0)
    return;
   int i = 0;
   int j = 0;
   for(; i < length ; i++)
   {
     int key = a[i];
     for(j = i ; j >= 1; j--)
     {
       // 2 4 3
       if(a[j-1] > key)
         a[j] = a[j-1]; 
       else 
         break;
     }
       //注意越界
       if(j <= 0)
       {
         j = 1;
       }
       a[j-1] = key;
   }
}
int main()
{
 // int a[] = {4,2};
  int a[] = {4,3,2};
  insertion(a,sizeof(a)/sizeof(a[0]));
  for(auto i : a)
  {
    cout << i << " ";
  }
  return 0;
}
