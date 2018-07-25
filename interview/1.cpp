#include<stdio.h>
#include<iostream>
using namespace std;
#define Max(a,b) ((a) > (b) ? (a):(b))
union test 
{
  short a;
  char buf[2];
};


class __TrueType 
{
};
class __FalseType 
{
};
template<class T>
struct _TypeTraits 
{
  typedef __FalseType IsPodType;   
};

template<  >
struct _TypeTraits<int>
{
  typedef  __TrueType IsPodType;
};

template<typename T>
void myadd(T&a, T&b,__TrueType f)
{
  cout << "int called" << endl;
}
template<typename T>
void myadd( T&a,  T&b, __FalseType f)
{
  cout << "other called" << endl;
}

template<typename T>
T myadd(T& a, T&b)
{
  return myadd(a,b,_TypeTraits<T>::IsPodType );
}

int main()
{
  int a=  0;
  int b = 0;
  cout << myadd(a,b);
}


