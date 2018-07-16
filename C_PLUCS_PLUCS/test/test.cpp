#include<iostream>
using namespace::std;
class A
{
  public:
    A()
    {
      printf("A constructor\n");
    }
    virtual void fun()
    {
      cout << "A :: fun()" << endl;
    }
    void function()
    {
      cout << "A :: function()" << endl;
    }
};
class B :public A
{
  public:
    B()
    {
      cout<< "B constructor"  << endl;
    }
    void fun()
    {
      cout << "B :: fun()" << endl;
    }
    void function()
    {
      cout << "B :: function()" << endl;
    }
};
class C: public B 
{
  public:
    C()
    {
      cout<< "C constructor"  << endl;
    }
    void fun()
    {
      cout << "C :: fun()" << endl;
    }
};

int main()
{

  A* a1= new B();
  a1->fun();

  

  //A a2 = B();
  //a2.fun();
}
