#include<iostream>
#include<vector>
using namespace std;
int InversePairs_r(vector<int> &data) { 
  size_t  i = 0;
  int count = 0;
  for(; i < data.size();i++)
  {
    for(size_t j = i + 1; j < data.size(); j++)
    {
      if(data[i] > data[j])
      {
        count++;
      }
    }
  }
  return count;
}
int  Merge(vector<int> &data,vector<int>&help,int begin,int mid,int end)
{
  int count = 0;
  for(int i = begin; i < end ; i++)
  {
    help[i] = data[i];
  }
  int left_last = mid -1;
  int right_last = end -1;
  int copyIndex = end - 1;
  while(left_last >= begin && right_last >= mid)
  {
    if(help[left_last] > help[right_last])
    {
      count += right_last - mid +1;
     data[copyIndex--] = help[left_last--];
    }
    else 
    {
      data[copyIndex--] = help[right_last--];
    }
  }
  for(; left_last >=begin;left_last--)
  {
    data[copyIndex--] = help[left_last];
  }
  for(; right_last >=mid;right_last--)
  {
    data[copyIndex--] = help[right_last];
  }
  return count;
}
int MergeSort(vector<int> &data,vector<int>&help,int begin,int end)
{
  if(begin + 1 >= end)
    return 0;
  int mid = begin + (end- begin) / 2;
  int left = MergeSort(data,help,begin,mid);
  int right = MergeSort(data,help,mid,end);
  int count = Merge(data,help,begin,mid,end);
  return left + right + count;
}
int InversePairs_core(vector<int> &data,vector<int> &help,int begin,int end)
{
  if(begin + 1 >= end)
  {
    help[begin] = data[begin];
    return 0 ;
  }
  int mid = begin + (end- begin) / 2;
  int left = InversePairs_core(help,data,begin,mid);
  int right = InversePairs_core(help,data,mid,end);
  int count = 0;
  int left_last = mid -1;
  int right_last = end -1;
  int copyIndex = end - 1;
  while(left_last >= begin && right_last >= mid)
  {
    if(data[left_last] > data[right_last])
    {
      count = count + right_last - mid + 1; 
      help[copyIndex--] = data[left_last--];
    }
    else 
    {
      help[copyIndex--] = data[right_last--];
    }
  }
  for(; left_last >=begin;left_last--)
  {
    help[copyIndex--] = data[left_last];
  }
  for(; right_last >=mid;right_last--)
  {
    help[copyIndex--] = data[right_last];
  }
  return right + left + count;
}
int InversePairs(vector<int> &data)
{
  vector<int> copyVector(data.size());
  int ret = InversePairs_core(data,copyVector,0,data.size());
  size_t i = 0;
  for(; i < data.size() ; i++)
  {
    cout << copyVector[i];
  }
  return  ret;
}

int main()
{
  //vector<int> v ={7,5,6,4};
  vector<int> v = {6,3,1,5,4};
  vector<int> help(v.size());
  //cout << MergeSort(v,help,0,v.size());
  cout << InversePairs_r(v);
  //auto i = 0;
  //for(; i < v.size() ; i++)
  //{
    //cout << v[i];
  //}
  return 0 ;
}


