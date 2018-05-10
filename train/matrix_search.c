#include<stdio.h>
int array[][4] =
{
    {2, 4, 9,10},
    {3, 8,16,17},
    {5,14,19,20},
};
int size_row = sizeof(array)/sizeof(array[0]);
int size_col = sizeof(array[0])/sizeof(array[0][0]);
void matrix_search(int key )
{
    int i = size_row ;
    int j = size_col;
    printf("size_row = %d, size_col = %d\n",  i,  j);
    int start_point = size_row - 1;
    for( i = 0, j = size_col - 1; i < size_row && j > 0;  )
    {
        if( key < array[i][j]  )
        {
            j--;
        }
        if( key > array[i][j] )
        {
            i++;
        }
        if( key == array[i][j] )
        {
            printf("find location: (%d,%d)",i , j);
            return;
        }
    }
    printf(" not find \n");
    return;
}
//插入就像二叉堆的上浮或者下沉
void insert( int value )
{
    /*int i,j,max;*/
    /*if( i == 0 && j == 0 )*/
        /*break;*/
    /*if( i ==  0  )*/
        /*max = a[i][j-1];*/
    /*else if( j == 0  )*/
        /*max = a[i+1][j];*/
    /*else*/
    /*{*/
        /*maze = a[i][j-1] > a[i-1][j] ? 1 :2;*/
    /*}*/
}
int main()
{
    matrix_search(16);
    return 0;
}
