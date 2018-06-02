#include<vector>
#include<iostream>
using namespace ::std;
vector<size_t> col_index(8);
  void Permutation(size_t k );
void InitEightQueen()
{
  size_t i = 0;
  for(; i < col_index.size(); i++)
  {
    //col 0 到 7 不能重复(同一列)
    col_index[i] = 0;
    //数组下标不重复,所以行一定不重复
  }
  Permutation(0);
}
int g_count = 0;
//把 列(0 到 7)全排列, 剔除主对角线和副对角线

//注意是任意两个皇后都不能 是对方的对角线
bool Islegal()
{
  size_t i = 0;
  size_t j;
  for( ; i < col_index.size() - 1; i++ )
  {
    //对角线 1行等于2列 && 1列等于 2 行 
    //福对角线  1行+1 等于2行,  1列+1 等于2列
    for(j = i + 1 ; j < col_index.size(); j ++ )
    {
      if( i - j == col_index[i] - col_index[j] || j - i == col_index[i] - col_index[j] )
      {
        return false; 
      }
    }
  }
  return true;
}
void Swap(int a, int b)
{
  size_t tmp = col_index[a];
  col_index[a] = col_index[b];
  col_index[b]  = tmp;
}
void Permutation(size_t k)
{
  if( k == col_index.size() )
  {
    if(Islegal())
    {
      cout<< "find right way"<< endl;
      g_count++;
    }
    return;
  }
  else 
  {
    size_t i;
    for( i = k; i < col_index.size(); i++ )
    {
      Swap(i,k);
      Permutation(k+1);
      Swap(i,k);
    }
  }
}
int main()
{
  InitEightQueen();
  cout<< g_count<< endl;
}


