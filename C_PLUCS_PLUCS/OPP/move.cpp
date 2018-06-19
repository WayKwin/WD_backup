#include<iostream>
class B
{
  public:
  B():mem(0){std::cout<< "B Constructer "<< std::endl;};
  B(const B& b) 
  {
   mem = b.mem; 
   std::cout<< "B Copy COnstructer" << std::endl;
  }
  private:
  int mem;

};
class A
{
  public:
  A():b(new B()) {std::cout << "A Constructer " << std::endl;}
  A(const A& a):b(new B(*(a.b))){ std::cout<< "A Copy Constructer " << std::endl; }
  A( A&& a):b(a.b){a.b = nullptr; std:: cout << "A Move Constructer" << std::endl;};
  private:
  B* b;
};
static A getA()
{
  A a;
  return a;
}
int main()
{
  A a;
  std:: cout << "=============================="<<std::endl;
  A a1(a);
  std:: cout << "=============================="<<std::endl;
  A a2(std::move(a));
}
