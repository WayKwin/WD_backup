#include<iostream>
using namespace::std;
class Cat
{
  public:
      Cat()
      {
            cout << "im cat" << endl;
              
      }
        int weight = 1;
};
class Tiger 
{
  public:
      Tiger()
      {
            cout << "im cat" << endl;
              
      }
        int Tiger_weight = 2;

};
//左继承 内存分布
class LittleTiger : public Cat, public  Tiger //和mafile一样递归展开
{
public:
  LittleTiger()
    {
        cout << "im cat" << endl;
    }
  int Little_Tiger = 3;
};
int main() 
{
  //更直观的写法
  LittleTiger *p = new LittleTiger();
  int* c = &p->weight;
  cout << *c << endl;
  c++;
  cout << *c << endl;
  c++;
  cout << *c << endl;
}
