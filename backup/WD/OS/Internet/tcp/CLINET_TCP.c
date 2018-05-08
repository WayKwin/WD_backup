#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<error.h>
#define BUFF_SIZE 128
int main(int argc, char* argv[])
{
     if( argc != 3 )
     {
        printf("usage: %s  IP Port \n", argv[0]);
        return 1;
     }
    struct sockaddr_in ser_addr;
    ser_addr.sin_family  = AF_INET;
    ser_addr.sin_port = htons(atoi(argv[2]));
    /*ser_addr.sin_addr.s_addr = inet_addr(argv[1]);*/
    inet_pton(AF_INET, argv[1], &ser_addr.sin_addr);
    int sock= socket(AF_INET, SOCK_STREAM, 0);
    if( sock < 0)
    {
        printf("socket error \n");
        return 1;
    }
    int ret  = connect( sock, (const struct sockaddr*)&ser_addr,
             sizeof(ser_addr) );
    if( ret < 0 )
    {
        printf("connect error ,errstring is :%s \n", strerror(ret));
        return 2;
    }
    char buf[BUFF_SIZE];
    while(1)
    {
        buf[0] = 0;
        printf("please enter # ");
        fflush(stdout);
        //a b c \n
        // s - 1 = \n  将其置零
        ssize_t s =read(1, buf, sizeof(buf));
        //将 \n 变成 0  字符串结尾 \n  字符串大小 s
        if( s > 0 )
        {
            if( strcmp(buf, "quit") == 0 )
            {
                printf(" quit now!\n");
                break;
            }
            else
            {
                buf[s - 1] = 0;
                write(sock, buf, strlen(buf));
            }
        }
        else if( s < 0 )
        {
            printf("read error \n");
            /*continue;*/
        }
    }
    close(sock);
    return 0;
}
