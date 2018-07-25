#include<iostream>
using namespace std;
template<typename T>
void myadd(T& lhs,T&rhs)
{
  cout << " geric function called"<<endl;
}
template<>
void myadd(int& a,int& b)
{
  cout << " 特化 called" <<endl;
}
class TrueType 
{
    
};
class FalseType
{

};
int main()
{
  //int a = 3;
  //int b = 4;
  //char a = 3;
  //char b = 4;
  //myadd(a,b);
}
