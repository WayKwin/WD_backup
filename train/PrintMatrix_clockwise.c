#include<stdio.h>
/* 打印方式
 *  1 2 3 4
 *  -     -
 *        5
 * -      6
 * 10 9 8 |7
 注意特殊对待 横线和竖线
void printfMartix(int a[1][1],size_t size_row, size_t size_col,int start_i,\
        int start_j)
{
    int i = start_i;
    int j = start_j;
    //上
    for(i = start_i, j = start_j; j < size_col ; j++)
    {
        printf("%d ",a[i][j]);
    }
    //打完一行 防止横线
    if(  start_i == size_row-1  )
        return;
    //右
    for(i = start_i + 1 ,j = size_col - 1 ; i < size_row ; i++)
    {
        printf("%d ",a[i][j]);
    }
    //打完一列,防止竖线
    if(start_j == size_col - 1)
       return;
    //下
    for(i = size_row - 1, j = size_col -2 ; j > start_j ; j-- )
    {
        printf("%d ",a[i][j]);
    }
    for( j = start_j, i = size_row - 1;  i > start_i; i-- )
    {
        printf("%d ",a[i][j]);
    }
}
int main()
{
    /*int array[3][3] =*/
    /*{*/
        /*{1, 2, 3},*/
        /*{8, 8, 4},*/
        /*{7, 6, 5},*/
    /*int array[3][4] =*/
    /*{*/
        /*{1, 2, 3, 4},*/
        /*{10, 11, 12, 5},*/
        /*{9, 8, 7, 6},*/
    /*};*/
    int array[4][1] =
    {
        {1},
        {2},
        {3},
        {4},
    };
    int i;
    int j;
    int size_row = sizeof(array)/sizeof(array[0]);
    int size_col = sizeof(array[0])/sizeof(array[0][0]);
    printf("row : %d, col:  %d\n", size_row, size_col);
    int end_col = ( size_col + 1  )/ 2;
    int end_row = (size_row + 1) / 2;
    for(i = 0, j = 0; i < end_row && j < end_col ; i++, j++)
    {

        printfMartix(array, size_row, size_col,i, j);
        size_row -= 1;
        size_col -= 1;
    }
    printf("\n");
}
