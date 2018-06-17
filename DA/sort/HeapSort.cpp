#include<iostream>
#include<vector>
using namespace::std;
void Swap(int &a,int &b)
{
  int tmp = a;
  a = b;
  b = tmp;
}
void sink(vector<int> &numbers,size_t start)
{
  if(start >numbers.size() )
    return;
  size_t size = numbers.size();
  int parent = start / 2;
  while(parent > 0)
  {
    size_t child = 2 * parent + 1;
    if(child + 1 < size && numbers[child + 1] > numbers[child])
    {
      child += 1;
    }
    if(numbers[parent] < numbers[child])
    {
      Swap(numbers[parent],numbers[child]);
    }
    parent = (parent - 1) / 2;
  }
}
void dealTop(vector<int> &numers,size_t tail);
{
  swap(numers[0],numers[tail]);
  sink()
}
