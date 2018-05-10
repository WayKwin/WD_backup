#include<arpa/inet.h>
#include<stdio.h>
int main()
{
    struct sockaddr_in addr1,addr2;
    addr1.sin_addr.s_addr = 0;
    addr2.sin_addr.s_addr = 0xffffffff;
    char *a1 = NULL;
    char*a2 = NULL;
    a1 = inet_ntoa(addr1.sin_addr);
    a2 = inet_ntoa(addr2.sin_addr);
    printf("address 1 : %s,address 2: %s\n", a1, a2);
    return 0;
}
