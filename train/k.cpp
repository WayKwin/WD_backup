#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
int kElem(vector<int> elems,int n)
{
#if 0
  vector<int>::iterator  begin = elems.begin();
  vector<int>::iterator end = elems.end();
  vector<int>::iterator cend = elems.end();
  vector<int>::iterator ret =  partition(begin,end,[](int a, int b)->bool{return a < b;});
  while(ret != cend -n)
  {
    if(ret > cend-n)
    {
      end = ret; 
    }
    else 
    {
      begin = ret + 1;
    }
    ret =  partition(begin,end,[](int a, int b){return a < b;});
  }
  return *ret;
#endif
}
int main()
{
  vector<int> a =  {1,2,3,4,5};
  sort(a.begin(),a.end(),[](int a,int b){return a < b;});
  //cout << kElem(a,1);
}
