#include<iostream>
#include<map>
#include<set>
#include<string>
#include"../Class/Sales_Data.h"
using namespace::std;
bool compareIsbn(const Sales_Data&s1, const Sales_Data&s2)
{
  return s1.isbn() < s2.isbn();
}
bool (*fun)( const Sales_Data&,const Sales_Data&)  = compareIsbn;
//set<Sales_Data,fun> b;
set<Sales_Data,decltype(compareIsbn)* > c;
//set<Sales_Data,[](const Sales_Data&s1, const Sales_Data&s2){s1.isbn()>s2.isbn()}> c;
//set<Sales_Data,bool(compareIsbn*)( Sales_Data&,const Sales_Data&)> c;
void countWords()
{
  map<string,size_t> word_count;
  string word;
  set<string> exclude = {"the","but","and"};
  auto iter = exclude.find("the");
  cout << *iter;
  while(cin >>word)
  {
    //set find 返回指向元素的迭代器,若没有找到返回尾后迭代器
    if( exclude.find(word ) == exclude.end())
         ++ word_count[word];
  }

  for(const auto &w: word_count)
  {
    cout << w.first << "occurs"  << w.second << ((w.second > 1)? "times":"time") << endl;
  }
}
void testSet()
{
  //set 存的是pair 类型 
  //set 和map 的迭代器都是在只读迭代器
  
}
int main()
{
  countWords();
}

