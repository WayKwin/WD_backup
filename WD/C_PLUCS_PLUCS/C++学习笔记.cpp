#include<iostream>
#include<string>
using namespace::std;
class Sales_Data
{
	//������Ԫ����(��Щ�������ⲿ�ĺ������Է�������private���εĳ�Ա������) ps.public����˭�����Է���
	//��Ԫ���������⻹Ҫ�������� һ��,��ν���������Щ������"��Ԫ"
	friend Sales_Data add(const Sales_Data&, const Sales_Data&);
	friend ostream& print(ostream&, const Sales_Data&);
	friend istream& read(istream&, Sales_Data&);
public:
	//���캯��
	Sales_Data(const string&s, unsigned n, double p) ;
	Sales_Data(std::istream &is);
	Sales_Data();
	//��Ա����
	string isbn()const { return this->bookNo; };
	Sales_Data& combine(const Sales_Data&);
private:
	double avg_price()const;
	//��Ա����
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
//���캯�� ,�����ⶨ�幹��ǵ�����������
Sales_Data::Sales_Data() = default;
Sales_Data::Sales_Data(const string&s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n){};
Sales_Data::Sales_Data(std::istream &is)  { read(is, *this); }
// �ӿں���
Sales_Data add(const Sales_Data&, const Sales_Data&);
ostream& print(ostream&, const Sales_Data&);
istream& read(istream&,  Sales_Data&);
//��Ա������ʵ��
double Sales_Data::avg_price() const// ��const ��˼���ǲ��޸ĳ�Ա����
{                                   // (const Sales_Data* const this)this�Դ��ڶ�������const
	if (units_sold)
		return revenue / units_sold;
	return 0;
}
Sales_Data&  Sales_Data::combine(const Sales_Data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;//thisָ�򱾶���,������;
}
//�ӿں���ʵ��
Sales_Data add(const Sales_Data&lhs, const Sales_Data&rhs)
{
	//ע��lhs��const����,������lhs.combine;
	Sales_Data sum = lhs;
	sum.combine(rhs);
	return sum;
}
//IO���ڲ��ɿ�����������
istream& read(istream &is, Sales_Data &item)
{
	double price = 0;
	cin >> item.bookNo >> item.units_sold >> price;
	return is;
}
ostream& print(ostream& os, const Sales_Data &item)
{

}
