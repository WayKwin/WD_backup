#include<iostream>
#include<list>
#include<deque>
using namespace::std;
list<deque<int> > l;
deque<int> q1,q2;
int main()
{
  q1.push_back(1); 
  q1.push_back(2); 
  q1.push_back(3); 
  q2.push_back(4);
  q2.push_back(5);
  l.push_back(q1);
  l.push_back(q2);
  auto iter_l_begin = l.cbegin();
  auto iter_l_end  = l.cend();
  while(iter_l_begin != iter_l_end)
  {
    auto iter_q_begin = iter_l_begin->begin(); 
    auto iter_q_end = iter_l_begin->end(); 
    while(iter_q_begin != iter_q_end)
    {
      cout << *iter_q_begin;
      iter_q_begin++;
    }
    iter_l_begin++;
  }
  cout<< endl;
}
