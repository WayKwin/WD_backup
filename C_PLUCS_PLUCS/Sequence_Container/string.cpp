#include<string>
#include<vector>
#include<iostream>
#include<list>
using namespace::std;
void CopyContainer()
{
  vector<string> v1{"waykwin", "jack","tom"};
  //容器类型不能拷贝
  //list<string> l1(v1);
  vector<string> v2(v1);

  //迭代器只用元素类型相同即可
  auto begin = v1.begin();
  auto end = v1.end(); 
  list<string> l1(begin,end);
  auto begin_list =l1.begin();
  auto end_list = l1.end();
  while(begin_list != end_list)
  {
    cout<< *begin_list;
    ++begin_list;
  }
//  while(l1.begin() != l1.end())
//  {
//    cout << *l1.begin();
//    ++l1.begin();
//  }
}
int main()
{
  CopyContainer();
  string s = "abcd";
  auto begin = s.cbegin();
  auto end = s.cend();
  //使用迭代器返回初始化容器,迭代器类型必须相同
  string s2(begin,end);
  cout<< s2 << endl;
  //范围初始化
  vector<int> v1;
  v1 = {1,2,3,4};
  //wrong
  //v1{1,2,3,4};
  //列表初始化, 构造函数 
  vector<int> v2{1,2,3,4};
 // while(begin < end )
 // {
 //  cout<< *begin << endl; 
 //  begin++;
 // }
  return 0;
}
