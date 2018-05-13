#include<iostream>
#include<vector>
#include<string>
using namespace ::std;
vector<string> wordlist = {"got", "dot", "god","lot","log"};
string input = "hot";
string output = "dog";
int swap(string s1,string s2)
{
  int differ_count = 0;
  auto iter1 = s1.begin();
  auto iter2 = s2.begin();
  while(iter1 != s1.end())
  {
    if(*iter1 == *iter2)
    differ_count++; 
    iter1++;
    iter2++;
  }
  return differ_count;
}
int wordChange()
{

  if( swap(input,output) == 1) 
  {
    return (1); 
  }
  return
}
