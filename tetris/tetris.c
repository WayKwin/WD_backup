#include<stdlib.h>
#include<stdio.h>
#define N 10
void roata(int arr[N][N], int a, int b, int c, int d)
{
  for(int i = 0; i < d-b; i++)
  {
    int tmp = arr[a][b+i];
    arr[a][b+i] = arr[c-i][b];
    arr[c-i][b] = arr[c][b-i];
    arr[c][b-i] = arr[c-i][d];
    arr[c-i][d] = tmp;
  }
}
int arr(int arr[N][N])
{

}
int main()
{
  for(int i = 1; i <=9; i++ )
  {
    for(int j = 1; j <=i;j++)
    {
      /*printf("\033[10;7H\n");*/
      printf("%d*%d=%d ",j,i,i*j);
    }
    printf("\n");
  }
  return 0;
}
      /*int tmp = arr[a][b + i];*/
      /*arr[a][b+i] = arr[c-i][b];*/
      /*arr[c-i][b] = arr[c][d-i];*/
      /*arr[c][d-i] = arr[a+i][d];*/
      /*arr[a+i][d] = tmp;*/
