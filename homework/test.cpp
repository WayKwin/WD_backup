#include<unordered_map>
#include<iostream>
#include<map>
using namespace std;
int main()
{
  unordered_map<int,int> s;
  s.insert({1,2});
  ::map<pair<int,int>,pair<int,int> > m2;
  m2.insert({ {1,3},{3,2} });
  auto ret = m2.find({1,3});
  cout << ret->first.second;
}
