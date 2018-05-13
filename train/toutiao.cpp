#include<iostream>
#include<vector>
#include<algorithm>
using namespace::std;
int Need( vector<int> &v)
{
  vector<vector<int> > total;
  sort(v.begin(),v.end());
  int count = 0;
  int container = 2;
  size_t i = 1;
  while( i  < v.size() )
  {
    //可以放
    if(v[i] - v[i - 1] <= 10)
    {
      container--;     
      //放满了
      if(container == 0)
      {
        //下一个容器肯定能放一个 
        container = 2;
      }
      if( i ==  v.size() - 1 )
      {
        count += container;
        break;
      }
    }
    //不能放
    else 
    {
      //判断需要几个
      count += container;
      container = 2;
      //最后一个
      if( i == v.size() - 1 )
      {
        count += container;
        break;
      }
      //重新开始
    }
    i++;
  }
  return count;
}
int main()
{
  // 最后一个数字直接加下状态的container
  vector<int> v = {10,21,32};
  cout << Need(v);
}
