#include<stdio.h>
int CanBuyIt[50][50];
int BuyJuzi(int n)
{
  int i = 0;
  int j = 0;
  for( i = 0; i * 8 < n; i ++)
  {
   for( j = 0; j * 6 < n; j++ )
   {
      CanBuyIt[i][j] = i * 6 + 8 * j; 
   }
  }
  int size_row= i;
  int size_col = j; 

  for( i = 0; i <= size_row; i ++ )
  {
    for( j = )
  }
  
  return 0;
}
