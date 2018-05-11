#include<sstream>
#include<iostream>
#include<vector>
using namespace::std;
struct PersonInfo{
  string name;
  vector<string> phones;
};
void intToString()
{
  int a = 10;
  string s;
  stringstream stream;
  stream << a;
  stream >> s;
  cout << s << a << endl;
}
void StringAppend()
{
  stringstream stream;
  string s,b;
  stream<< "hello";
  stream<< "world";
  s.append("abcd");
  b = "fghj";
  s.swap(b);
  cout << stream.str() << endl << s << endl  << b << endl;
 }
int main()
{
  StringAppend();
  intToString();
//  string line,word;
//  vector<PersonInfo> people;
//  while(getline(cin,line)){
//    PersonInfo info;
//    istringstream record(line);
//    record >> info.name;
//    while(record >> word)
//      info.phones.push_back(word);
//    people.push_back(info);
  }

