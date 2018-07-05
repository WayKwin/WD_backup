#include<iostream>
class Data
{
  public:
    Data()=delete;
    Data(int year, int month,int day);
    Data(const Data& rhs);
  private:
    bool IsLeap();
    constexpr const static  int leap_year[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    constexpr const static  int normal_year[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int _GetDayByMonth(const int year,const int day);
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

