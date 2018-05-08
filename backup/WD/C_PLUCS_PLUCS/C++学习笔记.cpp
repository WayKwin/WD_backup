#include<iostream>
#include<string>
using namespace::std;
class Sales_Data
{
    //¿¿¿¿¿¿(¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿provate¿¿¿¿¿¿¿¿)
    //¿¿
    //¿¿ public¿¿¿¿¿¿¿¿
    //¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿, ¿¿¿¿¿¿¿¿ "friend"
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
    //¿¿¿¿
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
//¿¿¿¿
Sales_Data::Sales_Data() = default;
Sales_Data::Sales_Data(const string&s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n){};
Sales_Data::Sales_Data(std::istream &is)  { read(is, *this); }
//¿¿¿¿
Sales_Data add(const Sales_Data&, const Sales_Data&);
ostream& print(ostream&, const Sales_Data&);
istream& read(istream&,  Sales_Data&);
//³ÉÔ±º¯ÊýµÄÊµÏÖ
double Sales_Data::avg_price() const// ´øconst ÒâË¼ÊÇÊÇ²»ÐÞ¸Ä³ÉÔ±±äÁ¿
{                                   // (const Sales_Data* const this)this×Ô´øµÚ¶þ¸ö¶¥²ãconst
	if (units_sold)
		return revenue / units_sold;
	return 0;
}
Sales_Data&  Sales_Data::combine(const Sales_Data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;//thisÖ¸Ïò±¾¶ÔÏó,½âÒýÓÃ;
}
//½Ó¿Úº¯ÊýÊµÏÖ
Sales_Data add(const Sales_Data&lhs, const Sales_Data&rhs)
{
	//×¢ÒâlhsÊÇconstÐÞÊÎ,²»¿ÉÒÔlhs.combine;
	Sales_Data sum = lhs;
	sum.combine(rhs);
	return sum;
}
//IOÊôÓÚ²»¿É¿¿±»¿½±´ÀàÐÍ
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
