#include<stdio.h>
#include<ctype.h>
#include<string.h>
// 字符串翻转  welcome to bat 变为 bat  to welcome
// 思路:先整个翻转字符串 ,然后碰到空格,一次翻转
// 注意判断条件 要判断 \0 当 hi = \0 翻转完 要break;
void reverseChar(char* str,int lo,int hi)
{
  while(lo < hi)
  {
    char tmp = str[lo];
    str[lo] = str[hi];
    str[hi] = tmp;
    lo++;
    hi--;
  }
}
void reverseChar(char* str)
{
  int lo = 0;
  int hi = 0;
  int length = strlen(str);
  reverseChar(str,lo,length-1);

  while(1)
  {
    while(str[hi] != '\0' && !isspace(str[hi]) )
    {
      hi++;
    }
    //找到空格 往前退一个
    hi--;
    reverseChar(str,lo,hi);
    //注意此判断条件 
    if(str[hi]== '\0')
      break;
    // w c 
    // 从w跳过空格到c
    hi+=2;
    lo = hi;
  }
}
int main()
{
  char str[] = "welcome to bat";
  //int length = strlen(str);
  reverseChar(str);
  printf("%s\n",str);
}
