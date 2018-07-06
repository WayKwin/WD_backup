#include"Data.h"
const int Data::leap_year[] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
const int Data::normal_year[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
bool Data::IsLeap( const int _year)
{
  if(( _year %400 == 0 && _year %100 != 0 )|| _year %400 == 0)
  {
    return true;
  }
  return false;
}
int Data::_GetDayByMonth(const int year,const int month)
{
  if(month == 2)
  {
    if(IsLeap(year))
    {
      return leap_year[month];
    }
  }
  return normal_year[month];
}
Data::Data(int year, int month = 1,int day = 1)
  {
    if(year < 0 || month < 1 || month > 12|| day < 0)
    { 
      throw "invalid input" ;
    }
    _year = year;
    _month = month;
    if(IsLeap(_year))
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
Data::Data(const Data& rhs)
  {
      _year = rhs._year;
      _month = rhs._month;
      _day = rhs._day;
  }
//前置++ 无参数,后置++有参数 (区分方法)
Data& Data::operator++()
{
  *this += 1;
  return *this;
}
//后置的++ 效率并不高
Data  Data::operator++(int)
{
  Data ret(*this);
  ret += 1;
  *this = *this + 1;
  return ret;
}
int  Data::operator-(const Data & data) const
{
  int flag = 1;
  Data  ago= data;
  Data  future = *this; 
  int day = 0;
  if(future  < ago)
  {
    Data tmp = future;
    future = ago;
    ago = tmp;
    flag = -1;
    //std::cout<< "yes";
  }
  //future.Display();
  //ago.Display();
  while(ago != future)
  {
    ++day;
    ++ago;
  }
  return day*flag;
}
// > 和== 可以推出其他
Data& Data::operator=(const Data & data)  
{
  if(data == *this)
    return *this;
  _year = data._year;
  _month = data._month;
  _day = data._day;
  return *this;
}
bool Data::operator== (const Data & data) const
{
  return _year == data._year && _month == data._month && _day == data._day;
}
bool Data::operator!= (const Data & data) const
{
  return !(*this == data);
}
bool Data::operator < (const Data& data) const
{
  return !( *this >= data ); 
}
bool Data::operator <= (const Data& data) const
{
  return !(*this > data);
}
// > 和== 可以推出其他
bool Data::operator > (const Data& data) const
{
  return _year > data._year || _month > data._month || _day > data._day;
}
bool Data::operator >= (const Data& data) const
{
  return  *this > data || *this == data;
}
Data& Data::operator+=(const int& day) 
{
  if(day  < 0)
  {
    //BUG
    //_day -= (-day);
    *this -= (-day);
  }
  else 
  {
    _day += day;
    while(_day > _GetDayByMonth(_year,_month))
    {
      // 减去 这个月的天数就是这个月多出来的天数
      _day -= _GetDayByMonth(_year,_month);
      if(_month == 12)
      {
        _month = 1;
        _year++;
      }
      else 
        _month++;
    }
  }
  return *this;
}
Data Data::operator+(const int& day)  const
{
  //这是新创建了一个临时变量来 进行 -= 所以不会修改*this const ok
  Data ret (*this);
  //if(day < 0)
    //// day 小于零 在+= 中  的_day 不可能 > 这个月的总天数(31 + -1)没问题 但是(31 - 66) 不会进入while循环
    //ret -=  (-day);
  //else 
  ret += day;
  return ret;
}

Data Data::operator- (const int& day) const
{
  Data ret(*this);
  // 坑 bug 这里 会出现 2017 1 -122 天
  //ret._day -= day; 已经重载了 对象的 减法 ,不能用成员变量天数来减
  
// ( 31 - (-100)  )   -=不会进入下面那个while循环
  //if(day < 0 )
    //ret += (-day);
  //else 
  ret -= day;
  return ret;
}

Data& Data::operator-=(const int& day)
{
  if( day <  0)
  {
    //BUg
    //_day += (_day);
    *this += (-day);
  }
  else 
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
          throw " out of range ";
        ;
      }
      _day += _GetDayByMonth(_year,_month);
    }
  }
  return *this;
}
void Data::Display() const
{
  std::cout << _year << '-' <<  _month << '-' << _day << std::endl;
}
std::istream& operator>>(std::istream& in,Data& data)
{
  in >> data._year >>data._day>>data._month >>data._day;
  return in;
}
std::ostream& operator<<(std::ostream& out,Data const& data)
{
  out  << data._year <<data._day<<data._month <<data._day;
  return out;
}
