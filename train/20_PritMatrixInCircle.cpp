#include<iostream>
using namespace::std;
void PrintMatrixInCircle(int ** numbers,int columns,int rows,int start)
{
  int startRow = start;
  int startColumn = start;
  int endRow = rows - start - 1;
  int endColumn = columns - start - 1;
  int  i;
  // 第一次打印左到右边
  for( i = startColumn ; i  <= endColumn; i++)
  {
    cout << numbers[startRow][i];   
  }
  //如果有两行,就打印上到下
  if(startRow < endRow)
  {
     i = startRow + 1;
    for(; i <= endRow; i ++)
    {
     cout << numbers[i][endColumn]; 
    }
    // 如果有两行两列 打印右到左
    if( startColumn < endColumn )
    {
      i = endColumn - 1;
      for( ; i >= startColumn; i--)
      {
        cout << numbers[endRow][i];
      }
      // 如果有至少三行 打印下到上 
      if( startRow + 1 < endRow )
      {
        i = endRow - 1;
        //注意这里不打印startRow
        for(; i > startRow; i--)
        {
          cout<< numbers[i][startColumn];
        }
      }
    }
  }
}
void PrintMaxtrixClockwisely(int ** numbers, int columns, int rows)
{
  if( numbers == NULL || columns <=0 || rows <=  0)
    return;
  int start = 0;
  while(columns > 2 * start && rows > 2 * start)
  {
    PrintMatrixInCircle(numbers, columns, rows, start);
  }
}
