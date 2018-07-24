#include<iostream>
#include<vector>
#include<algorithm>
using namespace::std;
int NeedNum(vector<int>& num)
{
 sort(num.begin(),num.end()); 
 int i = 0;
 int count  = 0;
 for(;(size_t)i < num.size(); i+=3)
 {
    int begin = i;
    int mid = begin + 1;
    int end = begin+2;
    if(mid >= num.size())
    {
      count+=2;
      return count;
    }
    if(end >= num.size())
    {
      count+=1;
      return count;
    }
    int ret = (num[mid] - num[begin])/10;
    if(ret - 1 > 0 )
    {
      count += ret-1;
      if(( num[mid]-num[begin])%10 != 0)
        count++; 
    }

    ret = (num[end] - num[mid])/10;
    if(ret - 1 > 0 )
    {
      count += ret-1;
      if(( num[end]-num[mid])%10 != 0)
        count++; 
    }
 }
 return count;
}
int main()
{
  //vector<int> num = {20,50,80};
  //vector<int> num = {20,21,22};
  vector<int> num = {20,31,32};
  cout << NeedNum(num);
}
