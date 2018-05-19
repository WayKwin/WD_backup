#include<iostream>
#include<string>
using namespace::std;
class Sales_Data
{
  //在类中声明友元函数
	friend Sales_Data add(const Sales_Data&, const Sales_Data&);
	friend ostream& print(ostream&, const Sales_Data&);
	friend istream& read(istream&, Sales_Data&);
public:
    //defalut constructer
	Sales_Data(const string&s, unsigned n, double p) ;
  // copy constructer
  Sales_Data(const Sales_Data&);
	Sales_Data(std::istream &is);
	Sales_Data();
    //member function
	string isbn()const { return this->bookNo; };
	Sales_Data& combine(const Sales_Data&);
private:
	double avg_price()const;
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
//默认构造器
Sales_Data::Sales_Data() = default;
//拷贝构造器
Sales_Data:: Sales_Data(const Sales_Data& ori): bookNo(){};

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
//接口函数实现
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

   return NULL;
}
