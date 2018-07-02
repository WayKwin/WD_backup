#include<iostream>
//struct A
//{
  //float a;
  //float c;
  //int b;
//};
//int main()
//{
  //A a;
  //std::cout << a.a  << ' '<< a.c << ' '<< a.b ;
//}
class A
{
  public:
  static int static_num;
  int num;
  void static fun();
};

void A::fun()
{
  std::cout<< "static fun";
}
class B
{
  public:
    //这里没有报错,但是实例化B会出错 说const常量没有被赋值
  const int num ;
  //解决上面报错
  B():num(10){};
};
class C
{
  public:
    //这里如果没有赋值(定义)会报错 说对num没有定义的引用
    const static int num = 10; 
    //所以区分和B的区别
};
struct D_help 
{
  //typedef  int bar;
  //static int bar;
};
//int D_help::bar = 10;
template <typename  T>
class D
{
  public:
  static T static_a;
  void func(T &c);
  int a =10;
};
template <typename T>
void D<T>::func(T &c)
{
  //这是 size_type的静态变量和p相乘
  //还是一个size_type 类型的指针
  //T::size_type * p;
  //所以使用 typename 声明这是一个类型
}
template <typename T>
T D<T>::static_a = 10;

int main()
{
  A::static_num = 10;
  D<int>::static_a = 19;
  //D<int> d;
  //d.static_a = 11;
  //d.a = 11;
  //D<int> d2;
  //std::cout<< d2.static_a << d2.a;
  //B b1;
  //C c;
  //std::cout << c.num;
  //A a1;
  //a1.num = 11;
  //A a2;
  //std::cout << a2.num;
}
