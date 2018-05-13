#include<iostream>
#include<vector>
std:: vector<int> v(1000,1);
void Isprimer(std::vector<int> &v)
{
  int i = 2;
  int j;
  for( i = 2; i * i < 1000; i++ )
  {
    if(v[i])
    {
      for(j = 2 * i;  j < 1000; j += i)
      {
        v[j] = 0;
      }
    }
  }
  int m = 150; 
  int n = 100;
  while( n + 2 <= m)
  {
    if(v[n] &&v[n + 2])
    {
      std::cout<< n << " "<< n + 2;
      n += 2;
    }
    else 
      n++;
  }
}
int main()
{
  Isprimer(v);
}
