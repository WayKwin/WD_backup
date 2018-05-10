#include<stdio.h>
#include<ctype.h>
long long  ExcelCol( char* str )
{
    if(str == NULL)
        return -1;
    long long i = 0;
    while(*str)
    {
        if( !isupper(*str) )
        {
            printf("invlid input \n");
            return -1;
        }
       i *= 26 +  ( *str-'\0'- 64 );
       str++;
    }
    return i;
}
int main()
{
    char* s = "AB";
    int a = ExcelCol(s);
}
