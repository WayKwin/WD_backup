#include<iostream>
class Data
{
  public:
    Data(int year = 0, int month = 1,int day = 1)
    {
      if(year < 0 || month < 1 || month > 12|| day < 0)
      { 
        throw "invalid input" ;
      }
      _year = year;
      _month = month;
      if(IsLeap())
      {
        if (day > leap_year[month])
        {
          throw "invalid input" ;
        }
      }
      else 
      {
        if (day > normal_year[month])
        {
          throw "invalid input" ;
        }
      }
      _day = day;
    }
  private:
    bool IsLeap();
    constexpr const static  int leap_year[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    constexpr const static  int normal_year[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int _GetDayByMonth(const int year,const int day);
    Data operator- (const int& day);
    Data& operator-=(const int & day);
    int _year;
    int _month;
    int _day;
};
bool Data::IsLeap()
{
  if(( _year %400 == 0 && _year %100 != 0 )|| _year %400 == 0)
  {
    return true;
  }
  return false;
}
Data Data::operator- (const int& day)
{
  Data ret(*this);
  // 坑 bug 这里 会出现 2017 1 -122 天
  //ret._day -= day;
  
  ret -= day;
  return ret;
}
Data& Data::operator-=(const int & day)
{
  _day -= day;
  //坑 bug  会出现 2015 1 0 
  //while(_day < 0)
  while(_day < 1)
  {

      _month--;
      if(_month < 1)
      {
        _month = 12;
        _year--;
        if(_year < 0)
          //TODO
          ;
      }

      _day += _GetDayByMonth(_year,_month);
  }
  return *this;
}
