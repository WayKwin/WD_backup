#include<string>
#include<vector>
#include<iostream>
#include<list>
using namespace::std;
//容器的拷贝``
void CopyContainer()
{
  vector<string> v1{"waykwin", "jack","tom"};
  //容器类型不能拷贝
  //list<string> l1(v1);
  vector<string> v2(v1);

  //迭代器只用元素类型相同即可(或者元素类型可以相互转换``)
  auto begin = v1.begin();
  auto end = v1.end(); 
  list<string> l1(begin,end);
  auto begin_list =l1.begin();
  auto end_list = l1.end();
  int a = 10;
  double b = 1.0;
  a = b;
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
// 容器的交换
void SwapContainer()
{
  // 只要求元素类型相同,交换比赋值快
  // 赋值缺点: 左容器相关的迭代器引用和指针会失效
  list<int> l1{1, 2, 3, 4};
  vector<int> l2{5,6,7,8};
  l1.swap(l1);
  //assign
  list<string> l;
  vector<const char*>v2;
  auto i1 = l.cbegin();
  auto i2 = l.cend();
  v2.assign(i1,i2);
  //初始化的时候使用迭代器也可以
  vector<const char*>v3{i1,i2};
}
// 总结 在初始化时或者之后的赋值,交换操作
// 迭代器是无关容器类型的
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
