#include<iostream>
int absPower_1(double base, int exponent)
{
  while(--exponent)
  {
    base  *= base;
  }
  return base;
}
int equal(double num1, double num2)
{
  if(num1 - num2 > -0.0000001 &&
      num1 - num2 < 0.00000001)
    return 1;
  return 0;
}
double absPower(double base, int a)
{
  if(a == 0)
    return 1;
  if(a == 1)
    return base;
  int result = absPower(base, a >> 1);
    result *= result;
  if( a &  0x1)
    result *= base;
  return result;
}
double power(double base, int exponent)
{
  // base > 0 exponet > 0 base *= base
  // base = 0 exponet ?   return 1
  // base < 0  normal
  //  exponet <  0  base *= base  1 / base  base != 0
  // double 比较错误
  if(equal(base,0 ))
    return 0.0;
  if( exponent == 0 )
    return 1;
   int absExponet;
  if( exponent < 0 )
    absExponet = -exponent;
  else 
    absExponet = exponent;
    
  double ret  = absPower(base,absExponet);
  if( exponent <  0)
    return 1.0 / ret;
  else 
    return ret;
}

int main()
{
  double base = 2;
  int exponent = -2;
  std::cout << power(base,exponent) <<std::endl;
  return 0;
}
