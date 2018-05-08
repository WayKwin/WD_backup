/*
 * 旋转数组中找到最小值,
 * 4 5 1 2 3
 * 规律是   前边 4 5 是排序好的 后面1 2 3 也是排序好的
 * 考虑使用折半查找,最小值肯定是后面的数组中第一个
 * mid = 1 ;  mid >= begin时表明mid还在第一个数组中
 * 当mid <=  begin时表明 mid已经在第二个数组中了
 * 而且当 end - begin = 1时 begin和end分别到达了 MAX和Min
 * 因为和折半查找一个规律  begin永远是递增的而end永远是递减的 因为:
 *       mid 若是比begin小 , begin就不会等于mid
 *       mid 若是比end 大, end 永远不会等于mid
 *  注意此方法依赖begin mid 和 end 大小来判断 若三个相等就无法进行有效的判断了
 * 此时只能顺序查找
 */
#include<stdio.h>
int min(int* array,size_t length)
{
    if(array == NULL || length == 0)
    {
        printf("invalid input\n");
        return -1;
    }
    int begin = 0;
    int end = length - 1;
    // begin mid end 如果三者都一样 就无法判断指针的移动了
    while(end > begin)
    {
        if(end - begin == 1)
        {
            return array[end];
        }
        int mid = begin + ( end - begin ) / 1;
        //wrong way!!!
        /*if( array[mid] == array[begin] == array[end] )*/
        if((  array[mid] == array[begin]  )&& ( array[begin] == array[end] ) )
        {
            printf("start special method\n");
            int i = 0;
            for( ; i < length - 1; i ++  )
            {
                if( array[i] > array[i + 1] ) {
                    return array[i + 1];
                }
            }
            //顺序查找
        }
        if( array[mid] >= array[begin] )
        {
            begin = mid;
        }
        if( array[mid] < array[begin] )
        {
            end = mid;
        }
    }
    return -1;
}
int main()
{
    int array[] = {4, 5, 1, 2, 3};
    int array_2[] = {1, 0, 1, 1, 1};
    printf("min : %d\n", min(array_2, 5));

}
