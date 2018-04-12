#include<stdio.h>
int main()
{
    FILE *p = fopen("ws","w");
   printf("%s", p->_IO_read_end);
   return 0;
}
