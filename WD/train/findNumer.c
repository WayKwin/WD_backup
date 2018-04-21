#include<stdio.h>
void findMulNumber(int *a,int len)
{
    int i =0;
    for( ; i < len; i++ )
    {
        // 依次往后检查不科学, 5 4 3 2 1 是n^2 注意数组下标寻址
        /*for(; j < len; j++) {*/
            /*if(a[i] != i)*/

        /*}*/
        //a[2] != 2
        //a[2] = 1
        //a[a[2]] = 1
        //mark a[2]
        while( a[i] != i )
        {
            if(a[a[i]] == a[i])
            {
                printf(" %d",a[i] );
                return;
            }
            int tmp = a[i];
            a[i] = a[a[i]];
            a[a[i]] = tmp;
        }
    }
    return;
}
int main()
{
    int array[5] = { 4, 3, 0, 2, 1 };
    findMulNumber(array,sizeof(array)/sizeof(array[0]));
    return 0;
}
