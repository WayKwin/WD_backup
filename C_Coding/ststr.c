#include<stdio.h>
char* strstr(char* str,char* to_find)
{
    while(*str)
    {
        if(*str == *to_find)
        {
            char* cur_str = str;
            char* cur_find =to_find;
            char* ret = cur_str;
            while(*cur_str == *cur_find)
            {
                //str不为空,没++前cur_find 必不为空
                cur_str++;
                cur_find++;
                if(*cur_find == '\0')
                {
                    return ret;
                }
            }
        }
        str++;
    }
}
int main()
{
    char* a = "abcdefg";
    char* b = "defg";
 printf("%s\n",strstr(a,b));
    return 0;
}
