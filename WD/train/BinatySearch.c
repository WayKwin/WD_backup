/*
 * 1.  返回命中元素
 * 2   可能有重复元素,返回第一次出现的元素
 * 3   可能有重复元素,返回最后一次出现的元素
 *
 */
#include<stdio.h>
int BinarySearch_1(int *a,int length, int key)
{
    if( a == NULL || length <= 0  )
    {
        return -1;
    }
    int lo = 0;
    int hi = length - 1;
    int mid = lo + (hi - lo ) / 2;
    // 1 2  找2
    //    lo < hi 找不到 2
    while( lo <= hi )
    {
        if( a[mid] < key )
        {
        //  1 2 找 2   lo不 + 1 死循环
            lo = mid + 1;
        }
       else if( a[mid] > key )
        {
            hi = mid - 1;
        }
        else if( a[mid] == key )
        {
            return mid;
        }
    }
    return -1;
}
int BinarySearch_2(int *a,int length, int key)
{
    if( a == NULL || length <= 0 )
        return -1;
    int lo = 0;
    int hi = length - 1;
    int mid  = lo +  ( hi - lo  ) / 2;
    // 3 3 找第一个三
    while( lo < hi )
    {
        if( a[mid] >= key )
        {
            hi = mid;
        }
        else if( a[mid] < key )
        {
            lo = mid + 1;
        }
        mid = lo + ( hi - lo ) / 2;
    }
    //结束循环后
    //1.  lo = hi   查看是否等于key
    return a[lo] == key? lo: -1;
}
/*
 * 判断第一次出现和最后一次出现 区别
 * 第一次出现运用了 除法总是向下取整的特点  和 hi 通过mid的除法总可以向左和lo汇合
 * 但判断最后一次出现就不能用此方法, 因为除法总是向左边取整的
 * 3 3  lo = 3 hi = 3
 * mid <= key
 * lo = mid
 * mid 总是在lo这一边
 *  所以遇到这种情况就应该结束循环
 *  由于标准中 在lo == hi 还要判断一次
 *   向左取第一次出现的解法 也在循环外面 lo == hi时判断了一次
 *   所以在向右边找最大的时候 应该先判断 hi 然后 判断lo
 *   3 4 5 key = 3
 *   hi = 4 lo = 3
 *
 */
int BinarySearch_3(int *a,int length,int key)
{
    if( a == NULL || length <= 0 )
        return -1;
    int lo = 0;
    int hi = length - 1;
    int mid  = lo +  ( hi - lo  ) / 2;
    // 3 3找第二个3
    while( lo < hi - 1 )
    {
        if( a[mid] <= key )
        {
            lo = mid;
        }
        else if(a[mid] > key)
        {
            hi = mid - 1;
        }
        mid = lo + ( hi - lo ) / 2;
    }
    //结束循环后先判断 hi  因为要返回最后一个出现的
    return a[hi] == key? hi : a[lo] ==key? lo : -1;
}
int main()
{
    int array[] = {1,2,3,3,3,4,5};00
    int length = sizeof(array)/sizeof(array[0]);
    int frist = BinarySearch_2(array,length,3);
    int last = BinarySearch_3(array,length,3); printf(" 3第一次出现的位置 :%d ,3第二次出现的位置 %d \n",frist, last);
    return 0 ;
}

