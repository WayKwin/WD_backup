#include<iostream>
#include<list>
#include<deque>
using namespace::std;
list<deque<int> > l;
deque<int> s;
int main()
{
  
  s.push_back(1);
  s.push_back(2);
  l.push_back(s);
  //迭代器的类型
  list<deque<int> > :: iterator iter1 = l.begin();
  auto iter2 = l.end();
  size_t i = 0;
  size_t j = 0;
  iter1->push_back(3);
  //deque中的迭代器
  auto iter3 = iter1->begin();
  for( ; i < l.size(); i++ )
  {
    for(; j < iter1->size(); j++)
    {
      cout<< *iter3; 
    }
  }
}
