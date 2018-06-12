#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace::std;
bool mycompare(string s1,string s2)
{
  string numbers1 = s1+s2;
  string numbers2 = s2+s1;
  return s1 >s2;
}
void PrintMinNumer(vector<int> numebrs)
{
  vector<string> ret(numebrs.size()) ;
  auto i = numebrs.cbegin();
  for(; i != numebrs.cend(); i++)
  {
     ret.push_back(to_string(*i)) ;
  }
  auto begin = ret.begin();
  auto end =ret.end();
  sort(begin,end,mycompare);
  size_t a = 0;
  for(; a < ret.size(); a++)
  {
   cout << ret[a]; 
  }
  cout <<endl;
}
int main()
{
  vector<int> numebrs= {3,32,321};
  PrintMinNumer(numebrs);
  
  return 0;
   
}
