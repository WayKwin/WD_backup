#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
using namespace std;
class TheFileSystem 
{ 
  public:
    TheFileSystem():dir(3),num(4){ cout << "构造函数called" << endl ;}
    void print()
    {
      cout << "tfs called" <<endl;
      cout << dir << endl;
      cout << num << endl;
    }
    static TheFileSystem& GetTFS()
    {
      static TheFileSystem tfs;      
      return tfs;
    }
  private:
    int dir = 3;
    int num = 4;
};
void func(void)
{
  // main函数结束后会执行 所有对象的析构函数 cout 也是
  //cout << "bye bye" << endl;
  printf("bye bye \n"); 
  //write(1,"bye bye",7);
}
int main()
{
  cout << "main start" << endl;
  atexit(func);
  //abort();
  exit(1);
  cout << "main end" << endl;
  return 0;
}

TheFileSystem tfs;


