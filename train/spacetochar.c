#include<stdio.h>
#include<string.h>
#include<ctype.h>
void spaceToChar(char* str)
{
    char* end = str;
    int count = 0;
    while(*end)
    {
        if(isspace(*end))
            count++;
        end++;
    }
    printf("count : %d\n", count);
    char* p_src = end;
    char* p_dst = end + 2 * count;
   while(p_src != p_dst)
   {
       if(!isspace(*p_src))
       {
           *p_dst = *p_src;
           p_src--;
           p_dst--;
       }
       else
       {
           p_src--;
           *p_dst-- = 'd';
           *p_dst-- = '2';
           *p_dst-- = '%';
       }
   }
   printf("%s\n",str);
}
int main()
{

    char a[100] = "we are happy";
    spaceToChar(a);
    return 0;
}
