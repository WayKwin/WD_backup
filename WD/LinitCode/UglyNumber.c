/*
 *
 *  1 , 2 ,3, 4 , 5 ,6 , 8 ,9
 *
 */
#include<stdio.h>
int Min(int a,int b, int c)
{
    int min =  a > b ? b : a;
    int m_min = min > c ? c : min;
    return m_min;
}
int UglyNumber(int n)
{
    int index2 = 0;
    int index3 = 0;
    int index5 = 0;
    const int length = n ;
    int Ugly[length];
    Ugly[0] = 1;
    int val;
    int index = 0;
    while( index < n )
    {
        int val = Min(Ugly[index2]*2, Ugly[index3]*3, Ugly[index5] *5);
        if( val == Ugly[index2]*2 )
        {
            index2++;
        }
        if( val == Ugly[index3]*3 )
        {
            index3++;
        }
        if( val == Ugly[index5]*5 )
        {
            index5++;
        }
        Ugly[index++] = val;
    }
    return Ugly[index];

}
int main()
{
    printf("%d\n ", UglyNumber(9));
    return 0;
}
