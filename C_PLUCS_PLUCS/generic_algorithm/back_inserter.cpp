#include<algorithm>
#include<vector>
#include<iostream>
#include<list>
using namespace::std;
void testBack_inserter()
{
  vector<int> vec;
  //插入迭代器可以插入元素
  auto iter= back_inserter(vec);
  fill_n(iter, 10, 0);
  //wrong vec为空
  fill_n(vec.begin(), 10,0);
  //right
  fill(vec.begin(),vec.end(),0);
}
void testCopy()
{
  vector<int>  vec = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> vec2(vec.size());
  //copy函数返回的是 拷贝完成后, 目的迭代器的尾后元素
  auto ret = copy(vec.cbegin(),vec.cend(),vec2);
}
void testReplace()
{
  list<int>  list = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> vec2;
  // 将vec 拷贝到vec2 并且将其中的 1 replace 为 0
  replace_copy(list.cbegin(),list.cend(), vec2.begin(), 1, 0);
  //和上面效果一样,不过使用了插入迭代器
  replace_copy(list.cbegin(),list.cend(), back_inserter(vec2), 1, 0);
}
void testUnique()
{
  //泛型算法不能改变容器大小,所以最后得使用容器自身方法改变其大小
  vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", 
                    "slow", "red", "turtle"};
  sort(words.begin(),words.end());
  auto iter = unique(words.begin(),words.end());
  //
  words.erase(iter, words.end());
}
