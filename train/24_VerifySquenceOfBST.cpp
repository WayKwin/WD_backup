#include<iostream>
using namespace::std;
// 不便于递归
//bool VerifySquenceOfBst(int* a, int a_length)
//{
  //if( a == NULL || a_length <= 0)
    //return false;
  //int root = a[a_length - 1];
  //int right_root = a_length - 2;
  //int i = a_length - 2;
  //for(; ; i--)
  //{
    //if(a[i] < root)
    //{
      //break;
    //}
  //}
  //int left_root = i;
  //for(; i >= 0; i--)
  //{
    //if(a[left_root] > root)
      //return false;
  //}



//}
bool VerifySquenceOfBst(int* a, int a_length)
{
  if( a == NULL || a_length <= 0)
    return true;
  int root = a[a_length - 1];
  int* left_root = a;
  int i = 0;
  while(a[i] < root)
  {
    i ++;
  }
  int left_length = i;
  int check_i = 0;
  for(; check_i < left_length; check_i++)
  {
    if(a[check_i] > root)
      return false;
  }
  // 左边检测合格,开始监测右边
  int* right_root = a + i;
  int right_length =a_length - left_length;
  check_i = i;
  for(; check_i < right_length; check_i ++)
  {
    if(a[check_i] < root)
      return false;
  }
  return VerifySquenceOfBst(left_root,left_length) && 
        VerifySquenceOfBst(right_root, right_length);
}
int main()
{
  int a[] = {5, 7, 6, 9, 11, 10, 8};
  int a_length = sizeof(a)/sizeof(a[0]);
  bool ret = VerifySquenceOfBst(a, a_length);
  cout<< ret;
}
