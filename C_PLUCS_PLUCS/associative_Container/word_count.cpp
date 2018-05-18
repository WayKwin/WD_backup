#include<iostream>
#include<map>
#include<string>
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::cin;

void wordCount()
{
  map<string,size_t> word_count;
  string word;
  while(cin >> word)
  {
    ++word_count[word];
  }
}
