#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace::std;
double MinD(vector<int>&numbers,int end)
{
  sort(numbers.begin(),numbers.end());
  auto i = numbers.begin();
  int MaxDistance = 0;
  int Distance = 0;
  int startDistance;
  int endDistance;

  for(; i != numbers.end() -1 ; i++)
  {
    Distance =  *(i + 1) - *i ;
    if(Distance > MaxDistance)
      MaxDistance = Distance;
  }
  double MidDistance = MaxDistance / 2.0;
  startDistance = numbers[0] - 0;
  printf("numbers[0]:%d\n",numbers[0]);
  printf("startDistance :%d\n",startDistance);
  endDistance= end - numbers[numbers.size() - 1]; 
  printf("numbers[1]:%d\n",numbers[1]);
  printf("endDistance :%d\n",endDistance);
  int  tmp = startDistance > endDistance ? startDistance : endDistance;
  return  MidDistance > tmp? MidDistance : tmp; 
}
int main()
{
  int num;
  int distance;
  scanf("%d%d",&num,&distance);
  printf("num: %d.distance:%d\n",num,distance);
  // 错误这里已经分配好了num.然后又用pushback
  //vector<int> numbers(num);
  vector<int> numbers;
  int input;
  while(scanf("%d",&input) != EOF)
  //while(cin>>input)
  {
    numbers.push_back(input);
    printf("input:%d\n",input);
  }
  printf("%.2f",MinD(numbers,distance));
}
