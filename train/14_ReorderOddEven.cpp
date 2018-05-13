#include<iostream>
#include<vector>
using  namespace::std;
void  ReorderOddEven(vector<int> &v1)
{
  int start = 0;
  int end = v1.size() - 1;
  while(start != end)
  {
    while(end != start && ( v1[end] & 0x1 ) == 0)
    {
      end--; 
    }
    while(end != start && (v1[start] & 0x1) == 1)
    {
      start++;
    }
    if( start != end )
    {
      int temp = v1[end];
      v1[end] = v1[start];
      v1[start] = temp;
    }
  }
}
int main()
{
  vector<int> v1 = {1,2,3,4,5,6};
  size_t  i = 0;
  ReorderOddEven(v1);
  for(; i != v1.size(); i++)
  {
    cout<< v1[i];
  }
  cout<< endl;
}
