#include<string>
#include<iostream>
using namespace::std;
double future(string s1,const string s2)
{
  auto i = s1.begin();
  for(; i < s1.end(); i++)
  {
    if(( *i <= 48 && *i >= 75 ) || ( *i>= 97 && *i <=122 ) || (*i>= 65 && *i <=90))
    {
      *i = '1';
    }
    else 
    {
      *i = '0';
    }
  }
  i = s1.begin();
  auto j = s2.begin();
  int count = 0;
  for(; i <s1.end();i++,j++)
  {
    if(*i == *j)
    {
      count++;
    }
  }
  

  return 0.0;
}
int main()
{

}
