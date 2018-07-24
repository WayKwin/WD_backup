#include<stdio.h>
#include<iostream>
using namespace std;
#define Max(a,b) ((a) > (b) ? (a):(b))
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

union test 
{
  short a;
  char buf[2];
};
template<typename T>
T myadd(T&a, T&b,__TrueType f)
{
  cout << "int called" << endl;
  return a + b;
}
template<typename T>
T myadd(T&a, T&b,__FalseType f)
{
  cout << "other called" << endl;
  return a + b;
}

template<typename T>
T myadd(T& a, T&b)
{
  return myadd(a,b,_TypeTraits<T>::IsPodType);
}


int main()
{
  cout << myadd(3,4);
}


