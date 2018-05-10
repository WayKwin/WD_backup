#include<stdio.h>
#define MAXSIZE 1000
//不需要数字数组.通过flag数组中的 0 1 打印下标就行了
/*int array[MAXSIZE];*/
int flag[MAXSIZE] ;
int main()
{
    int i = 0;
    int j;
    for(; i < MAXSIZE; i++)
    {
        flag[i] = 1;
    }
    for( i = 0; i < 2; i++ )
    {
        flag[i] = 0;
    }
    int rang = MAXSIZE;
    int last = rang - 1;
    for(  i = 2; i * i <rang; i++ )
    {
        /*printf("%d ", rang);*/
        if( flag[i] == 0 )
            continue;
        //注意不是 j = i  而是 j = 2*i
        //不能把2 3 也筛去
        /*for(j = i ; j < rang; j += i)*/
        for(j = 2 * i ; j < rang; j += i)
        {
            flag[j] = 0;
        }
        while( flag[last] == 0 )
        {
            last --;
        }
        /*rang = last;*/
        /*while(flag[j] == 0) {*/
            /*j--;*/
        /*}*/
        /*rang = j;*/
    }
    for( i = 2; i < MAXSIZE; i++ )
    {
        if( flag[i] == 1 )
            printf(" %d ", i);
    }
    printf("\n");
}
