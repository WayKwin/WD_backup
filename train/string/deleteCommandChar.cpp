#include<iostream>
#include<string.h>
#include<string>
// 题 1 在src 串中删除 sub串出现的字母 要求 时间复杂度o(n) 空间复杂度o(1)
// 
// 思路: 1 哈希表 256 保存 sub串
//  删除字符   src[i - count]  = src[i] 
//  遇到sub串的字符 count++;
using namespace::std;

char* DeleteCommandChar(char src[],int length,const string sub)
{
  char hash_table[256] = {0};
  for(auto i = sub.begin(); i != sub.end(); i++)
  {
    hash_table[*i]++;
  }

  int i = 0; 
  int count = 0;
  int j = 0;
  for(;i < length; i++,j++)
  {
    if(hash_table[src[i]] == 1 )
    {
      count++;
      continue;
    }
    //printf("[%d|%d] ",count,i);
    src[i-count] = src[i]; 
  }
  src[length-count]  = '\0';
  return src;
}

int main()
{
  char src[] = "They are student";
  const string sub = "aeiou";
  int length = strlen(src); 
  cout << DeleteCommandChar(src,length,sub);

  
} 
