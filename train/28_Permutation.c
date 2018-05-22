#include<stdio.h>
void Swap(char* a, char*b)
{
  if( *a == *b )
  {
    printf("相同交换%c\n",*a);
    return;
  }
  else 
    printf("不同交换\n");
  char tmp = *a;
  *a = *b;
  *b = tmp;
}
void _Permutation(char* Str,char* Begin)
{ 
  if(*Begin == '\0')
  {
    printf("%s\n",Str);
  }
  else 
  {
    for( char* Ch = Begin; *Ch != '\0'; ++Ch )
    {  
      Swap(Ch,Begin);
      _Permutation(Str,Begin + 1);
      //复位
      Swap(Ch,Begin);
    }
  }
}

void Permutation(char* str)
{
    if(str == NULL)
      return;
    _Permutation(str,str);
    printf("the last str: %s\n",str);
}
int main()
{
  char str[] = "ABC";
  Permutation(str);
}
