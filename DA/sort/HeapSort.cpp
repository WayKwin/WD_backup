#include<iostream>
#include<vector>
using namespace::std;
void Swap(int &a,int &b)
{
  int tmp = a;
  a = b;
  b = tmp;
}
void sink(vector<int> &numbers, size_t start,int tail)
{
  // 0 1 2 3 4  5 6 
  //if(start >= tail / 2 )
    //return;
  int  parent = start;
  //sink 拿到的是父节点,但是结束条件是 查看父节点是否是叶子节点
  //wrong while(parent < tail)
  while(parent * 2 + 1 < tail)
  {
      size_t child = parent * 2 + 1;
      if(child + 1 < tail && numbers[child] < numbers[child + 1] )
      {
        //右子树
          child += 1;
      }
      if(numbers[parent] < numbers[child])
      {
        swap(numbers[parent],numbers[child]);
      }
      else 
        //堆有序了, sink的本来就是一个堆 ,所以一旦有序就break
        break;
      parent = child;
  }
}
void PrintNumers(vector<int> &numbers);
void BuildHeap(vector<int> &numbers)
{
  // 碰到堆 想到 0 1 2
  int  start = numbers.size() / 2 - 1;
  // 0 也要下沉
  while(start >= 0)
  {
    sink(numbers,start,numbers.size());
    // 错误点1.直接找父节点.这里建应该  从后往依次
    //start = (start - 1) / 2;
    start--;
  }
}
void HeapSort(vector<int> &numbers)
{
  BuildHeap(numbers);
  int tail = numbers.size();
  while(tail > 0)
  {
    Swap(numbers[0],numbers[tail-1]);
    tail--;
    sink(numbers,0,tail);
    PrintNumers(numbers);
  }
}
void PrintNumers(vector<int> &numbers)
{
  auto i = numbers.begin();
  for(; i != numbers.end(); i++)
  {
      cout << *i;
  }
  cout << endl;
}
int main()
{
  vector<int> numbers= {1,0,2,4,3,5};
  HeapSort(numbers);
}
