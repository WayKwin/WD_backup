#include<iostream>
#include<string.h>
using namespace::std;
bool match(char* str, char* pattern)
{
  if( str == NULL || pattern == NULL)
    return true;
  char* i = str + strlen(str) - 1;
  char* j = str + strlen(pattern) - 1;
  //开始匹配模式
  while(i != str && j != pattern)
  {
    if(*j == '*')
    {
      j--;
      if( *j != *i  && *j != '.')
      {

        if( j == pattern )
          return false;
        while(* (j -1) == *j)
        {
          j--;
        }
      }
      //i he j 相等
      //
      while(*j == *i  || *j =='.')
      {
        if(*j == '.')
        {
          return true;
        }
        i--;
        if( i == str )
        {
          break;
        }
        //.* 
      }
      // aac
      // ba*c 
      while(* (j -1) == *j)
      {
        j--;
        if( j == pattern )
          break;
      }
    }
  
  }
}
int main()
{
  char*a = (char * )"aaa";
  
  //char*b = (char*)"a*";
  char*c =(char*) "bbb*...";
  //char*d = (char*)"ab*ac*.";
  cout<< match(a,c);
  return 0 ;
}
