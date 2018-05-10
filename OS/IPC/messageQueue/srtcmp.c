#include<stdio.h>
#include<string.h>
int cmp(char *a,char *b)
{
    return strcmp(a,b);
}
int main()
{
    char a[] = "abcd\n";
    char b[] = "abcd";
    char c[] = "abcd\0\n";
    char d[] = "abcd\0";
    printf("\\n和\\0\\n一样吗? %d\n",cmp(a,c));
    printf("%d\n",cmp(a,b));
    printf("----------------------\n");
    printf("%s",c);
    return 0;
}
