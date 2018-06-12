#include<iostream>
#include<vector>
using namespace::std;
int MaxSubArray(vector<int>& array)
{
  size_t i = 1;
  int NowSum = array[0];
  int MaxSum = array[0];
  for(; i < array.size(); i++)
  {
    if(NowSum <= 0)
    {
      NowSum = array[i];
    }
    else 
    {
      NowSum += array[i];
    }
    //每次都检测一下MaxSum是否要更新
    if(NowSum > MaxSum)
    {
      MaxSum = NowSum;
    }
  }
  return MaxSum;
}
int main()
{
  vector<int> Input = {-1,2,-1,4};
  cout<< MaxSubArray(Input) << endl;
}
