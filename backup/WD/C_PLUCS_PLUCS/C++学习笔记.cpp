#include<iostream>
#include<string>
using namespace::std;
class Sales_Data
{
    //真真真(真真真真真真真真provate真真真真)
    //真
    //真 public真真真真
    //真真真真真真真�, 真真真真 "friend"
	friend Sales_Data add(const Sales_Data&, const Sales_Data&);
	friend ostream& print(ostream&, const Sales_Data&);
	friend istream& read(istream&, Sales_Data&);
public:
    //constructer
	Sales_Data(const string&s, unsigned n, double p) ;
	Sales_Data(std::istream &is);
	Sales_Data();
    //member function
	string isbn()const { return this->bookNo; };
	Sales_Data& combine(const Sales_Data&);
private:
	double avg_price()const;
    //真真
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
//真真
Sales_Data::Sales_Data() = default;
Sales_Data::Sales_Data(const string&s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n){};
Sales_Data::Sales_Data(std::istream &is)  { read(is, *this); }
//真真
Sales_Data add(const Sales_Data&, const Sales_Data&);
ostream& print(ostream&, const Sales_Data&);
istream& read(istream&,  Sales_Data&);
//撹埀痕方議糞��
double Sales_Data::avg_price() const// 揮const 吭房頁頁音俐個撹埀延楚
{                                   // (const Sales_Data* const this)this徭揮及屈倖競蚊const
	if (units_sold)
		return revenue / units_sold;
	return 0;
}
Sales_Data&  Sales_Data::combine(const Sales_Data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;//this峺�魃抄塹�,盾哈喘;
}
//俊笥痕方糞��
Sales_Data add(const Sales_Data&lhs, const Sales_Data&rhs)
{
	//廣吭lhs頁const俐蔑,音辛參lhs.combine;
	Sales_Data sum = lhs;
	sum.combine(rhs);
	return sum;
}
//IO奉噐音辛真瓜申唄窃侏
istream& read(istream &is, Sales_Data &item)
{
	double price = 0;
	cin >> item.bookNo >> item.units_sold >> price;
	return is;
}
ostream& print(ostream& os, const Sales_Data &item)
{
   return NULL;
}
