#include<unordered_map>
#include<iostream>
#include<map>
#include<vector>
#include<string.h>
using namespace std;
int main()
{
  int num1 = 1;
  int  num2 = 2;
  
  char  str[]= "1,2";
  if(sscanf(str,"%d ,%d",&num1,&num2) != 2 )
    cout << "Sdsad\n";
  cout << num1 << " "<<num2 <<endl;
}
