#include<iostream>
#include<vector>
using namespace::std;
//并差集
void IsLandCore(vector<vector<int> > &matrix,int row,int col)
{
  if(row < 0||row >= matrix.size() || col >= matrix[0].size()|| col < 0 )
    return;
  if(matrix[row][col] == 0 )
    return;
  if(matrix[row][col] == 1)
    matrix[row][col] = 0;
  //
  IsLandCore(matrix,row+1,col);
  IsLandCore(matrix,row,col+ 1);
  IsLandCore(matrix,row-1,col);
  IsLandCore(matrix,row,col -1);
}
int CountLsland(vector<vector<int>> &matrix)
{
  int count = 0;
  //vector<vector<bool> >  IsVisted(matrix.size(),vector<bool>(0));
 for(int i = 0; i < matrix.size();i ++)
 {
   for(int j = 0; j < matrix[0].size();j++)
   {
      if(matrix[i][j] == 1)
      {
        count++;
        IsLandCore(matrix,i,j);
        void Display();
        Display();
      }
   }
 }
 return count;
}
vector<vector<int> > s = 
{
  {1,1,1,0},
  {1,0,0,0},
  {0,0,1,0},
  {0,1,1,0},
};
void Display()
{
  for(vector<int> i: s)
  {
    for(auto j : i)
    {
      printf("%d ",j);
    }
    cout << endl;
  }
  cout <<endl;
}
int main()
{

cout << CountLsland(s);
  
}
