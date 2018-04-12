#include<stdio.h>
#include<string.h>
#include<math.h>
int pow1(int n)
{
    int ret = 10;
    if( n == 0 )
        return 1;
    while(--n)
    {
        ret *= 10;
    }
    return ret;
}
int main()
{
    int ret = 0;
    char* str = "1234";
    int n = strlen(str) - 1;
    while(*str)
    {
        ret += (*str-'0') * pow1(n);
        str++;
        n--;
    }
    printf("%d",ret);
    return 0;
}
