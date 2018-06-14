#include<iostream>
#include<vector>
#include<string>
#include<memory>
//#include<
class strBlob
{
  public:
    typedef std::vector<std::string>::size_type size_type;
    strBlob();
    //列表初始化
    //和使用vector一样，我们也可以使用迭代器访问initializer_list里的元素
    strBlob(std::initializer_list<std::string> il);
    size_type size() const;
    bool IsEmpty() const;
    void push_back(const std::string & str);
    void push_front(const std::string & str);
    std::string& front();
    std::string& back();
  private:
   //共享指针
    std::shared_ptr<std::vector<std::string> > data;
    void check(size_type i,std::string & msg) const;
};
// make_shared 空vector
strBlob::strBlob():data(std::make_shared<std::vector< std::string> >()){}
//strBlob::strBlob():data(std::make_shared<std::vector< std::string> >("a","the")){}
//有限个string  可以初始化列表
strBlob::strBlob(std::initializer_list<std::string> ):data(std::make_shared<std::vector< std::string> > () ){}
void strBlob::push_back(const std::string & str)
{
  data->push_back(str);
}
std::string& strBlob::back()
{
    return data->back();
}
int main()
{
  //初始化列表只能这样初始化
  //提供initializer_list类的初衷，为了便于将有限个同一类型（或可转换为同一类型）的元素传递给函数。
  std::initializer_list<std::string> elem = {"a","the","and"};
  std::initializer_list<std::string> e;
  strBlob b(elem);
  strBlob c;
  //其实是调用了拷贝赋值运算符, 这里将data 赋值, 那么 共享指针是浅拷贝
  c = b; 
  //这才是拷贝复制构造函数
  strBlob d = b;
  b.push_back("or");
  std::cout<< c.back()<< std::endl; 
  return 0;
}

