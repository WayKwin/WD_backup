#include <iostream>
#include<vector>
using namespace ::std;
vector<int> v1(3);
void Swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
//bool Equal(int a, int b)
//{
  //a = 1;
    //return true;
  //return false;
//}

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
void Swap(int a, int b)
{
  int tmp = v1[a];
  v1[a] = v1[b];
  v1[b] = tmp;
}
void Combine(int k)
{
  if(k == v1.size() - 1)
  {
    int i = 0;
    while( i < v1.size() )
    {
      cout<< v1[i] << " ";
      i ++;
    }
    cout << endl;
  }
  else 
  {
    
    for( int i = k; i < v1.size() ; i++ )
    {
      Swap(k, i);
      Combine(k + 1);
      Swap(k,i);
    }
  }
}
int main()
{
  int i = 0;
  for(; i < 3; i++)
  {
    v1[i] = i + 1;
  }
  int array[] = {1,2,2};
  int k = 0;
  int length = sizeof(array)/sizeof(array[0]);
  Combine( k);
}
