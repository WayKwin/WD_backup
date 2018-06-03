#include<iostream>
class myclass
{
  public:
    int a;
    int b;
    myclass(): a(10),b(20){};
    //myclass();
    myclass(int c,int d){
      a = c;
      d = b;
    }
};
