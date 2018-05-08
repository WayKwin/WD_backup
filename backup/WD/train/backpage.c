#include<stdio.h>
#define item_number 3
#define packge_weight 5
#define Max(a,b) (a > (b) ? a : ( b ))
int value[] = { 0,7, 9, 1 };
int weight[] = { 0,3, 2, 1 };

int total_value[item_number + 1][packge_weight + 1] = {0};
int MaxValue(int i , int j)
{
    int i,j;
    if(i <0 || j < 0)
        return 0;
   return    total_value[i][j] = Max(total_value[i - 1][j], total_value[i - 1][j - weight[i]] + value[i]);
}
int main()
{
    int i,j;
    for(i = 0; i <= item_number; i++) {
        for( j = 0; j <= packge_weight; j++)
        {
            //背包承重为空, 没有物品
            if (i == 0 || j == 0 )
            {
                total_value[i][j] = 0;
                continue;
            }
            //第i件物品大于 当前的总重量
            //肯定换不了
            if( weight[i] > j )
                total_value[i][j] = total_value[i - 1][j];
            //
            else
            {
                // i - 1 写成 i
                /*total_value[i][j] = Max(total_value[i - 1][j], total_value[i][j - weight[i]] + value[i]);*/
                total_value[i][j] = Max(total_value[i - 1][j], total_value[i - 1][j - weight[i]] + value[i]);
            }
        }
    }
    for(i = 0; i <= item_number; i++) {
        for( j = 0; j <= packge_weight; j++)
        {
            printf("%2d ",total_value[i][j]);
        }
        printf("\n");
    }
        printf("\n");
    /*printf("%d \n", total_value[item_number][packge_weight]);*/
}
