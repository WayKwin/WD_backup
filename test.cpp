#include<stdio.h>
#include<stdlib.h>
#include<unordered_set>
#include<string>
using namespace std;
void fun()
{
  char* p;
  char* q;
  p = (char*) malloc(sizeof(char)*20);
  q = p;
  scanf("%s %s",p,q);
  printf("%s %s",p,q);
}
int main()
{
  unordered_set<char> s;
  s.insert('0');
  //char dst[1024];
  fun();

  //sprintf(dst,"%s%d","我的年龄",12);
  s.clear();
}
