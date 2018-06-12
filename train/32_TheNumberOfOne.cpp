#include<iostream>
using namespace::std;
int  CountNumber(int Number)
{
  int count = 0;
  while(Number)
  {
    if(Number %10 == 1)
      ++count;
    Number /= 10;
  }
  return count;
}
size_t TheNumberOfOne(int Number)
{
  int i = 0;
  int count = 0;
  for(; i <= Number; i++)
  {
    count+=CountNumber(i); 
  }
  return count;
}
//考虑 4  0 1
//     4  1 4
//     4  3 4
//     十位出现1的个数,和个位出现1的个数
int Better(int n)
{
  int base = 1;
  int count = 0;
  int round = n;
  while(round > 0)
  {
    int weight = round %10;
    round /= 10;
    count +=  base * round;
    if(weight == 1)
    {
      count += (n%base) +1;
    }
    else if(weight > 1)
    {
      count += base;
    }
    base *= 10;

  }
  return count;
}
int main()
{
  cout<< TheNumberOfOne(12) << endl;
  cout<<Better(12) << endl;
}
