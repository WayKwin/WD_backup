#include<iostream>
using  namespace std;
void test(int a, int b, int& count)
{
  if(count == 0)
    return;
  count--;
  cout << a <<endl;
  test(b,a,count);
}
int main()
{
  int count = 3;
    test(3,4,count);
}
