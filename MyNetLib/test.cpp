#include<iostream>
#include<list>
#include"threadpool.h"
using namespace::std;
//what fuck
template<typename T> void test(T a)
{
  list<T> b;
  b.push_back(a);
  cout<< b.front() << endl;
}
struct events 
{
  static int a;
  void process()
  {
    a++; 
    printf(" doing somethings,%d\n",a);
  }
};
int events::a= 0;
int main()
{
  events a;
  ThreadPool<events>* tp = ThreadPool<events>::GetThreadPool();
  printf(" main thread waiting \n");
  tp->SetEvents(&a);
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  return 0;
}
