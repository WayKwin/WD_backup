/*
 * 斐波那契的DP解法
 *  新新 = 新 + 旧
 *  新旧 =  新新 - 旧 (老新)
 *  扩展 上楼梯的问题
 */
#include<stdio.h>
long long Fibonacci(unsigned n )
{
    if( n <= 2)
        return 1;
    long long before = 1;
    long long after = 2;
    int i = 2;
    for( ; i < n ; i ++  )
    {
        after = after + before;
        before = after - before;
    }
    return after;
}
int main()
{
    printf(" %llu\n ",Fibonacci(5));
}

