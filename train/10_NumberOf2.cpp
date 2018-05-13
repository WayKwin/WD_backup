#include<iostream>
int NumberOf1(int a)
{
//没有这个 -1 会有32个1
  if(a < 0)
    a = -a;
  int count = 0;
  int flag  = 1;
  while(flag)
  {
    if(a&flag)
      count++;
    // 如果让a移动 a是负数 每次符号位还不变 >> 最后全f
    flag <<= 1;
  }
  return count;
}
int NumberOf1_Best(int a)
{
  if( a < 0 )
    a = -a;
  int count = 0;
  while(a)
  {
    a &= (a - 1);
    count++;
  }
  return count;
}
int main()
{
  int number  = -1;
  int ret = NumberOf1(number);
  int ret_2 = NumberOf1_Best(number);
  std::cout << ret<<std::endl; 
  std::cout << ret_2<<std::endl; 
}
