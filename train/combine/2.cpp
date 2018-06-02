#include<iostream>
#include<vector>
#include<string>
using namespace::std;
void Combination(string s,string:: iterator s_iter ,int number, vector<char> v)
{
  if(number == 0)
  {
    size_t i = 0;
    for(; i < v.size(); i ++ )
    {
      cout << v[i] << " ";
    }
    cout << endl;
  }
  if( s_iter ==  s.end() )
  {
    return;
  }
  v.push_back(*s_iter);
  Combination(s,s_iter+1,number - 1,v);
  v.pop_back();
  Combination(s,s_iter+1,number,v);
}
void getComBination(string s)
{
  auto iter = s.begin();
  for(size_t i = 0; i < s.size() - 1 ; i++ )
  {
    vector<char> v(s.size());
     
    Combination(s,iter,i,v);
  }
}
int main()
{
  string s = "abc";
  getComBination(s);
}

