#include<iostream>
#include<list>
#include<deque>
#include<stack>
using namespace::std;
list<deque<int> > l;

deque<int> q1,q2;


int main()
{

  stack<int> s;
  int a = 10;
  int &b  = a;
  int c = b;
  cout<< c;
  list<int> l1;
  int i  = 5;
  while(i--)
  {
    l1.emplace_back(i);
  }
  if(!l1.empty())
  {
    //访问成员函数都返回的是引用
    //用不用引用接收 由自己决定
    int& val = l1.front();
    //int &val2 = l1.at(3);
    
    val = val - 4;
  }
  
  cout<<l1.front()<<endl;
  //q1.push_back(1); 
  //q1.push_back(2); 
  //q1.push_back(3); 
  //q2.push_back(4);
  //q2.push_back(5);
  //l.push_back(q1);
  //l.push_back(q2);
  //auto iter_l_begin = l.cbegin();
  //auto iter_l_end  = l.cend();
  //while(iter_l_begin != iter_l_end)
  //{
    //auto iter_q_begin = iter_l_begin->begin(); 
    //auto iter_q_end = iter_l_begin->end(); 
    //while(iter_q_begin != iter_q_end)
    //{
      //cout << *iter_q_begin;
      //iter_q_begin++;
    //}
    //iter_l_begin++;
  //}
  //cout<< endl;
}
