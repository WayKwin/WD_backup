#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define BUFF_SIZE 128
void deal_msg(int sock,struct sockaddr_in* clinet_addr)
{
    /*printf(" in deal_msg:  连接套接字 %d \n",sock);*/
    int port = ntohs(clinet_addr->sin_port);
    char IPBuf[20];
    IPBuf[0] = 0;
    inet_ntop(AF_INET, (const void *) &clinet_addr->sin_addr, \
            IPBuf, sizeof(IPBuf));
    printf("[%s|%d]# connection established\n",IPBuf, port);
    char buf[BUFF_SIZE];
    buf[0] = 0;
    while(1)
    {
        ssize_t s = read(sock, buf, sizeof(buf) - 1);
        if( s > 0 )
        {
            buf[s] = 0;
            printf("[%s|%d]# %s\n", IPBuf, port, buf);
        }
        if( s  == 0 )
        {
            printf("[%s|%d]#  quit !\n",IPBuf, port);
            close(sock);
            break;
        }
        if( s < 0 )
        {
            printf("read error\n");
            sleep(1);
            continue;
        }
    }

}
struct info
{
    int sock;
    struct sockaddr_in clinet_addr;
    socklen_t len;
};
void* deal_sock(void * arg)
{
    struct info* sock_info   = (struct info*)arg;
    printf(" in deal_sock:  连接套接字 %d \n",sock_info->sock);
    deal_msg(sock_info->sock, &sock_info->clinet_addr);
    free(arg);
    return NULL;
}
int main(int argc,char* argv[])
{
    if( argc != 3 )
    {
        printf("usage : ./server Ip port \n");
        return 0;
    }
    struct sockaddr_in ser_addr;
    memset((void *)&ser_addr, 0 ,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(atoi(argv[2]));
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if( listen_sock < 0 )
    {
        printf("socket error \n");
        return 2;
    }
    if( bind(listen_sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) < 0 )
    {
        printf(" bind error\n");
        return 3;
    }
    if(listen(listen_sock, 3) != 0)
    {
        printf("listen error\n");
        return 4;
    }
    while(1)
    {
        struct info* sock_info = (struct info*)malloc(sizeof(struct info ));
        if(sock_info == NULL)
        {
            printf("malloc error \n");
            return 0;
        }
        struct sockaddr_in clinet_addr;
        //注意这里len虽然是输出型参数 但是 要根据len判断地址类型
        //所以必须用sizeof初始化!!!! 否则 ip 和port都是0
        socklen_t len = sizeof(clinet_addr);
        int sock;
        sock = accept(listen_sock, \
              (struct sockaddr *)&clinet_addr, &len);
        if( sock < 0 )
        {
            printf(" accept error \n");
            continue;
        }
        sock_info->sock = sock;
        sock_info->clinet_addr = clinet_addr;
        pthread_t  id;
        pthread_create(&id, NULL,  deal_sock, (void*)sock_info);
        pthread_detach(id);
    }
}
