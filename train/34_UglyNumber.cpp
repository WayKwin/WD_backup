#include<iostream>
#include<vector>
using namespace::std;
int min(vector<int> numbers,int a,int b, int c)
{
  int min = 3*numbers[a] < 5*numbers[b]? 3*numbers[a]:5*numbers[b]; 
  return min < 7*numbers[c]? min:7*numbers[c];
}
int IsUglyNumber_f(int numbers)
{
  while(numbers != 1)
  {
    if(numbers % 3 == 0)
    {
      numbers /= 3;
    }
    else if(numbers % 5 == 0)
    {
      numbers /= 5;
    }
    else if(numbers % 7 == 0)
    {
      numbers /= 7;
    }
    else 
      break;
  }
  return numbers == 1? true:false;
}
int  IsUglyNumber(int num)
{
  vector<int> numbers;
  numbers.push_back(1);
  int index_3 = 0;
  int index_5 = 0;
  int index_7 = 0;
  while( numbers.back() < num)
  {
  int min_val= min(numbers,index_3,index_5,index_7);
  if(min_val== numbers[index_3]*3)
  {
    index_3++;
  }
  if(min_val== numbers[index_5]*5)
  {
    index_5++;
  }
  if(min_val == numbers[index_7]*7)
  {
    index_7++;
  }
  numbers.push_back(min_val);
  }
  //cout<< numbers.size() << endl;
  if(numbers.back() != num)
  {
    return false;
  }
 return true;  
}

int main()
{
  cout<< IsUglyNumber_f(7) << endl;
}

