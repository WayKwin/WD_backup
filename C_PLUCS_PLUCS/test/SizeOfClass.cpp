#include<iostream>
using namespace::std;
class A
{
  A();
  //int a;
  //char b;
  //int c;
 virtual  ~A();

};
struct B
{
  int a;
};
int main()
{
  int *a ;
  cout <<  sizeof(a) << endl;
  return 0;
}
