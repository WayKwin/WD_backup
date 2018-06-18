#include<stdio.h>
#include<string.h>


//总结: 递归一定注意递归结束条件的先后顺序!!!!
bool CheckOutPath(const char matrix[][4],int rows,int cols, int pos_r,int pos_c, const char* msg,bool visitedPoint[][4])
{
  // 错误 这里如果 没判断该点是否走过就reutrn  baa 通过
  //if(*msg == '\0')
  //{
    //printf(" find a path\n");
    //return true;
  //}
  //bool hasPath = false;
  if(pos_r == rows || pos_c ==cols || pos_r < 0 || pos_c < 0) 
  {
    return false;
  }
  if(visitedPoint[pos_r][pos_c] == true)
    return false;
  visitedPoint[pos_r][pos_c] = true;
  if(*msg == '\0')
  {
    printf(" find a path\n");
    return true;
  }
  if(matrix[pos_r][pos_c] != *msg)
  {
    return false;
  }
  // 犯错,  如果此时msg 等于 0,会先判断上面那个if return false
  //if(*msg == '\0')
  //{
    //printf(" find a path\n");
    //return true;
  //}
if( CheckOutPath(matrix,rows,cols,pos_r + 1,pos_c,msg + 1,visitedPoint) || CheckOutPath(matrix,rows,cols,pos_r ,pos_c + 1,msg + 1,visitedPoint) ||
    CheckOutPath(matrix,rows,cols,pos_r - 1,pos_c,msg + 1,visitedPoint) || CheckOutPath(matrix,rows,cols,pos_r - 1,pos_c,msg - 1,visitedPoint)) 
  //只要一个方向 true 回溯过程都会return true
    return true;
  return false;
}
bool hasPathCore(const char matrix[][4],int rows,int cols, int row,int col, const char* msg,int& length,bool visitedPoint[][4])
{
  if(msg[length] == '\0')
  {
    return true;
  }
  bool hasPath = false;
  if(row >= 0 && row < rows && col >= 0
      && col < cols && matrix[row][col] == msg[length]  
      &&!visitedPoint[row][ col])
  {
      ++length;
      visitedPoint[row][col]= true;
    hasPath = hasPathCore(matrix,rows,cols,row,col-1,msg,length,visitedPoint) || hasPathCore(matrix,rows,cols,row - 1,col,msg,length,visitedPoint)||
      hasPathCore(matrix,rows,cols,row,col+1,msg,length,visitedPoint)||hasPathCore(matrix,rows,cols,row+1,col,msg,length,visitedPoint)  ;
    if(!hasPath)
    {
      --length;
      visitedPoint[row][col] = false;
    }
  }
  return hasPath;
}

bool HasPath(const char matrix[][4],int rows,int cols,const char* msg)
{
  //合法检测
  //找入口
  int i = 0;
  int j = 0;
  bool visitedPoint[rows][4];
  //memset(visitedPoint,0,sizeof(visitedPoint));
 int length = 0; 
  for(; i < rows;i++)
  {
   for(; j < cols; j++)
   {
     if(matrix[i][j] == *msg)
     {
      memset(visitedPoint,0,sizeof(visitedPoint));
      bool ret  = CheckOutPath(matrix,rows,cols,i,j,msg,visitedPoint);
      //bool ret = hasPathCore(matrix,rows,cols,i,j,msg,length,visitedPoint);
      if(ret == true)
        return true;
     }
   }
  }
  return false;
}
int main()
{
  char* msg = "abc";
  const char matrix[][4] = 
  {
    {'a','b','c','d' },
    {'e','f','g','h' },
    {'i','g','k','l' },
    {'m','n','o','p' },
  };
  bool ret = HasPath( matrix,3,4,msg);
  printf("%d",ret);
}

