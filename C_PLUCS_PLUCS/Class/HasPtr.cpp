#include<iostream>
#include<string>
//行为像值的类
//保证每个类都有自己的string深拷贝,而不是都指向统一块内存空间,浅拷贝
class HasPtr{
  public:
    HasPtr(const std::string &s = std::string()):ps(new std::string(s)),i(0){}
    HasPtr(const HasPtr& p):ps(new std::string(*(p.ps))),i(p.i){}
    HasPtr& operator=(const HasPtr&);
    ~HasPtr(){delete ps;} 
  private:
    std::string *ps;
    int i;
};
//拷贝运算符要注意传入自身,还能保证正确
//如果先 delete ps 
// 传入自身, rhs 也指向ps
// 就会出错
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
  //深拷贝
  auto newp = new std::string(*rhs.ps);
  //别忘了释放原来的内存
  delete ps;
  this->ps = newp;
  this->i = rhs.i;
  return *this;
}


