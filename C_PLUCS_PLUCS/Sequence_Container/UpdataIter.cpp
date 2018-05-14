#include<iostream>
#include<vector>
using std::vector;
using std::endl;
using std::cout;
void BadHabit()
{
  // 当我们要增加或者减少容器内的元素,
  // 不要用临时变量保存元素尾部的迭代器.
  // 因为尾部迭代器每次会更新
}
int main()
{
  vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7};
  vector<int>::iterator iter = v1.begin(); 
  while(iter != v1.end())
  {
    if( *iter & 0x1  )
    {
      // 在iter前插入一个相同元素,记得使用返回值跟新迭代器
      // insert返回 插入元素的位置
      iter = v1.insert(iter,*iter);
      iter += 2;
    }
    else 
    {
      // erase指向删除后的元素
      iter = v1.erase(iter);
    }
  }
  auto iter1 = v1.begin();
  while(iter1 != v1.end())
  {
    cout << *iter1;
    iter1++;
  }
  cout << endl;
  
}
