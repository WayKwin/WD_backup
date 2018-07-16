#include<iostream>
int main()
{
  int a = 1,b = 0, c = -1, d = 0;
  d = ++a||++b&&++c;
  std::cout << d << std::endl;
  return 0;
}
