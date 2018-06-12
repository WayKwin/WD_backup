#include<iostream>
#include<string>
using namespace::std;
class Sales_Data
{
  //在类中声明友元函数
	friend Sales_Data add(const Sales_Data&, const Sales_Data&);
  friend Sales_Data operator+ (const Sales_Data& lhs,  const Sales_Data &rhs);
	friend ostream& print(ostream&, const Sales_Data&);
	friend istream& read(istream&, Sales_Data&);
  //输入输出运算符必须是非成员函数
  friend ostream &operator<<(ostream&os, const Sales_Data& item);
  //输入参数第二个不应该改为const
  friend ostream &operator>> (istream &is,  Sales_Data &item);
public:
    //defalut constructer
	Sales_Data();
  //重载的构造函数
	Sales_Data(const string&s, unsigned n, double p) ;
	Sales_Data(std::istream &is);
  // copy constructer
  Sales_Data(const Sales_Data&);
  ~Sales_Data(){}
    //member function
	string isbn()const { return this->bookNo; };
	Sales_Data& combine(const Sales_Data&);
  //输入输出运算符必须是非成员函数
  //ostream &operator<<(ostream&os, const Sales_Data& item);

  //合成拷贝复制运算符
  Sales_Data& operator=(const Sales_Data &rhs);
private:
	double avg_price()const;
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

};
//默认构造器
