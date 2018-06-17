// 321 4
// 21 34
// 1 432 
// 12 43
// 32 41
#include<iostream>
#include<vector>
using  namespace::std;
const char* CanSort(vector<int> &numbers)
{
  size_t i = 0;
  bool fristDesc = 0;
  int lasTDescNumer = 0;
  for(; i < numbers.size()  -1;i++)
  {
    if(numbers[i] > numbers[i+1])
    {
      fristDesc = numbers[i];
      if( i+1 == numbers.size() - 1 )
      {
          lasTDescNumer =  numbers[i -1];
          break;
      }
    }
    else 
    {
      lasTDescNumer = numbers[i];     
      break;
    }
  }


}
