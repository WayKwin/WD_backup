#include <iostream>
using namespace::std;
void Swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
bool Equal(int a, int b)
{
  a = 1;
    return true;
  return false;
}
void Combine(int *array,  int k,int length)
{
  if(array == NULL)
    return;
  if(k == length - 1)
  {
    int i = 0;
    while( i < length )
    {
      cout<< array[i] << " ";
      i ++;
    }
    cout << endl;
  }
  else 
  {
    
    for( int i = k; i < length; i++ )
    {
      Swap(array + k, array + i);
      Combine(array,k + 1,length);
      Swap(array + k,array + i);
    }
  }
}
int main()
{
  int array[] = {1,2,2};
  int k = 0;
  int length = sizeof(array)/sizeof(array[0]);
  Combine(array,   k, length);
}
