#include<iostream>
#include<map>
#include<vector>
using namespace::std;

char fristNotReaptingChar(string& str)
{
  map<char,int> CharCount;
  auto i =  str.begin();
  for(; i != str.end(); i++)
  {
    CharCount[*i]++;
  }
  auto j = CharCount.begin();
  pair<char,int> a;
  for(; j != CharCount.end();j++)
  {
    if(j->second == 1 )
      return j->first;
  }
  //这里非法输入
  return 'a';
}
int main()
{
  string str = "aaabbc";
  cout << fristNotReaptingChar(str) <<endl;
}
