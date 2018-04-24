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
int  findMulNumber_version2(int *a, int len)
{
    if(a == NULL || len == 1)
        return -1;
    int low = 0;
    int high =  len -1;
    int cur = 0;
    int count = 0;
    while(low <= high)
    {
        int mid = low + (high - low) /2;
        cur = 0;
        while(cur < len - 1)
        {
            if(a[cur++] <= mid)
                count++;
        }
        if( count > mid )
        {
            high = mid - 1;
        }
        else low = mid + 1 ;
    }
    return a[low];

}
int main()
{
    int array[5] = {1 , 3, 2, 3,4};
    int ret = findMulNumber_version2(array,sizeof(array)/sizeof(array[0]));
    printf("%d\n", ret);
    return 0;
}
