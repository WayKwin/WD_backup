#include<iostream>
class Data
{
  friend std::istream& operator>>(std::istream&,Data& data);
  friend std::ostream& operator<<(std::ostream&,Data const& data);
  public:
    Data()=delete;
    Data(int year, int month,int day);
    Data(const Data& rhs);
  private:
    int _GetDayByMonth(const int year,const int day);
    bool IsLeap( const int _year);
    const static  int leap_year[13];
    const static  int normal_year[13];
  public:
    void Display() const ;
    Data  operator+ (const int & day) const;
    //Data& operator= (const Data& Data);
    Data& operator+= (const int & day);
    Data operator- (const int& day) const;
    //两个日期之差
    int operator- (const Data& day) const;
    Data& operator-= (const int & day); 
    Data& operator=(const Data & data);
    bool operator== (const Data & data) const;
    bool operator!= (const Data & data) const;
    bool operator> (const Data & data) const;
    Data operator++(int );
    Data& operator++();
    bool operator>= (const Data & data)const ;
    bool operator< (const Data & data)const;
    bool operator<= (const Data & data)const;
    int _year;
    int _month;
    int _day;
};

