#include"Sales_Data.h"
Sales_Data::Sales_Data() = default;
//拷贝构造函数
Sales_Data:: Sales_Data(const Sales_Data& ori): bookNo(ori.bookNo), units_sold(ori.units_sold), revenue(ori.revenue){};
//合成拷贝复制运算符
 Sales_Data& Sales_Data::operator=(const Sales_Data &rhs)
{
  this->bookNo = rhs.bookNo;
  this->units_sold = rhs.units_sold;
  this->revenue = rhs.revenue;
  return *this;
}

//初始化列表 初始化顺序是在类中的顺序!!!
Sales_Data::Sales_Data(const string&s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n){};
Sales_Data::Sales_Data(std::istream &is)  { read(is, *this); }
Sales_Data add(const Sales_Data&, const Sales_Data&);
ostream& print(ostream&, const Sales_Data&);
istream& read(istream&,  Sales_Data&);
//成员函数的实现
double Sales_Data::avg_price() const// 带const 意思是是不修改成员变量
{                                   // (const Sales_Data* const this)this自带底层const this就只指向本对象 不能改变
	if (units_sold)
		return revenue / units_sold;
	return 0;
}
Sales_Data&  Sales_Data::combine(const Sales_Data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;//this指向本对象,解引用;
}
/*友元函数*/
Sales_Data add(const Sales_Data&lhs, const Sales_Data&rhs)
{
	//注意lhs是const修饰,不可以lhs.combine;
	Sales_Data sum = lhs;
	sum.combine(rhs);
	return sum;
}
//IO属于不可靠被拷贝类型
istream& read(istream &is, Sales_Data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	return is;
}
ostream& print(ostream& os, const Sales_Data &item)
{

	os << item.bookNo << item.units_sold <<item.revenue;
   return os;
}
