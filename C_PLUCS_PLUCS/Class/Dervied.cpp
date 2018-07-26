#include<iostream>
#include<vector>
#include<algorithm>
using std::cout;
using std::endl;
class Cat 
{
  public:
  Cat()
  {
    std::cout << "无参构造函数 called" << std::endl;
  }
 Cat(int weight):weight(weight)
  {
    std::cout << "有参构造函数 called" << std::endl;
  }
 void virtual fun()
 {
   std::cout<< "父类虚函数" << std::endl;
 }
  private:
  int weight;
};
class Tiger :public Cat
{
  public:
  //Tiger(int weight):Cat(weight){}
  Tiger(){ std::cout << "子类的无参构造函数" << std::endl; };
  void fun()
  {
    std::cout << "子类虚函数" << std::endl;
  }
};
int main()
{
  std::vector<int> v = {1,2,3,3,3,4};
  //auto iter = remove(v.begin(),v.end(),3);
  //cout << *(iter- 1)<<endl;
  //auto iter = v.erase(v.begin());
  //cout << *(iter)<<endl;
  //auto iter = v.insert(v.begin(),10);
  auto iter = v.insert(v.end(),10);
  //cout << *(iter)<<endl;

  for(auto i:v)
  {
    cout << i << endl;
  }
  int a = 10;
  //Tiger t(a);
  Tiger t;
  return 0;
}
