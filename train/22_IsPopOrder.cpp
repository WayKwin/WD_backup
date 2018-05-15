#include<iostream>
#include<stack>
using namespace::std;
//  push 只管入栈  pop要和栈顶元素比较
bool IsPopOrder(const int* pPush, const int* pPop, int nlength)
{
  stack<int> s;
  bool bPossible = false;
  const int* pNextPush = pPush;
  const int* pNextPop = pPop;
  while(pNextPop - pPop < nlength)
  {
    //与栈中的比较
    //while(s.size() == 0 || *pNextPush != *pNextPop)
    // 入栈 pPush,
    while(s.size() == 0 || s.top() != *pNextPop)
    {
      s.push(*pNextPush);
      pNextPush++;
      //可以在这里直接返回false;
      if(pNextPush - pPush > nlength)
        break;
    }
    //是由于 栈满而退出循环
    if( pNextPush - pPush > nlength )
    {
      bPossible = false;
      break;
    }
    s.pop();
    pNextPop++;
  }
  if(pNextPop - pPop == nlength && s.size() == 0)
  {
    return true;
  }
  return false;
}
bool IsPopOrder_2(const int* pPush, const int* pPop, int nlength)
{
  stack<int> s;
  const int* pNextPush = pPush;
  const int* pNextPop = pPop;
  while(pNextPush - pPush < nlength)
  {
    //注意顺序, 先入栈再判断能否出栈
    //入栈 1 2 3  出栈 3 2 1
    //最后pNextPush ++ 会跳出循环 不会判断第二个while 了
   //如果不相等就入栈 
    s.push(*pNextPush);
    pNextPush++;
    while(s.size() != 0 && *pNextPop == s.top())
    {
      s.pop();
      pNextPop++;
    }
  }
  if( pNextPop - pPop >= nlength && s.size() == 0 )
  {
      return true;
  }
  return false;
}
int main()
{
  int a[] = {1,2,3};
  int b[] = {2,3,1};
  bool ret = IsPopOrder(a,b,3);
  bool ret_2 = IsPopOrder_2(a,b,3);
  cout<< ret;
  cout<< ret_2;
}


