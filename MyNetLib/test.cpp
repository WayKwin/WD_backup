#include<iostream>
#include<list>
#include"threadpool.h"
#include<string.h>
#include<strings.h>
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
  char text[1024] = "GET /usr/lcoal.jpg http/1.1";

  // 坑: strtok虽然方便, 但是内部用了静态变量,不适合多线程版

  //char* method =  strtok(text," ");
  //char* url =  strtok(NULL," ");
  //char* version =  strtok(NULL," ");

  char* method = text;
  char* cur = strpbrk(text," \t");
  *cur++ = '\0';

  char* url = cur;
  cur = strpbrk(url," \t");
  *cur++ = '\0';

  char* version = cur;
  if(strcasecmp(version,"HTTP/1.1") != 0)
    printf("not http/1.1\n");
  //cur = strpbrk(url," \t");
  //*cur++ = '\0';
  printf("%s\n",method);
  printf("%s\n",url);
  printf("%s\n",version);
  
  //events a;
  //ThreadPool<events>* tp = ThreadPool<events>::GetThreadPool();
  //printf(" main thread waiting \n");
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  return 0;
}
