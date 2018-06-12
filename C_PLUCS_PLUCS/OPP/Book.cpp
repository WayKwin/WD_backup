#include<iostream>
#include<string.h>
class Quote{
  public:
    Quote()= default;
    Quote(const std::string &book,double sales_price ): bookNo(book),price(sales_price){};
    //这里基类就可以用派生类来初始化
    //但是注意只能初始化基类存在的成员变量
    Quote(const Quote& p);
    std::string isbn(){return bookNo;}
    virtual double net_price(std::size_t n) const{ std::cout << "Quote" << std::endl;return n *price;}
    virtual ~Quote() = default;
  private:
    std::string bookNo;
  protected:
    double price = 0.0;
};
//派生类
class Bulk_qute:public Quote{
  public:
  Bulk_qute() = default;
  //重载构造函数
  Bulk_qute(const std::string &book,double, std::size_t,double);
  double net_price(std::size_t) const override;
  private:
  //满多少书才减免
  std::size_t min_qty = 0;
  //优惠力度
  double discount = 0;
};
double Bulk_qute::net_price(std::size_t) const
{
  std::cout << "Bulk_qute" << std::endl;
  return 0.0;
}
int main()
{
  Bulk_qute q;
  Quote c;
  //动态绑定
  Quote* ptr = &q;
  ptr->net_price(1);
  // 父类只能子类初始化
  // 不存在基类向派生类的隐式类型转换
  //Bulk_qute&p = c;
  //但是因为拷贝赋值构造函数和赋值运算符参数是 基类的引用,所以可以用派生类来初始化
  q.isbn();
}
