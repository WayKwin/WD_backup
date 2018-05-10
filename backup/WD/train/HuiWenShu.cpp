#include<iostream>
#include<string>
using namespace::std;
int HuiwenLenght(string s)
{
  int i = 0;
  int j = s.size() - 1;
  int count = 0;
  while( i < j )
  {
    if( s[i] == s[j]  )
    {
      i ++;
      j --;
    }
    else 
    {
      count++;
      i = 0;
      j = s.size() - count;
    }
  }
  if( i == j )
    return 2 * i + 1;
  else if( i > j )
    return 2 * i;
}
int main()
{
  string s;
  cin >> s;
  cout << HuiwenLenght(s) << endl;
  return 0 ;
}

