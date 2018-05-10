#include<stdio.h>
#include<stdio.h>
//atoi
#include<stdlib.h>

#include<unistd.h>
#include<sys/socket.h>
// inet_addr
#include<netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<string.h>
#define SERVER_PORT 8888
// sednto  需要知道往哪发的地址
// revfrom 可以想知道谁给我发的地址
// client 和 server 的区别
// 1. server需要bind绑定端口号
// 2.server 是先recv 再sendto
//   client是先sendto再recv
void udp_msg_sender(int fd, struct sockaddr* dst)
{
    socklen_t len;
    struct sockaddr_in WhoSendToMe;
    char buf[1024];
    while(1)
    {
        printf(" plase enter# ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf) - 1);
        if( s >  0)
        {
            buf[s] = 0;
            sendto(fd, buf, sizeof(buf), 0, \
                    (struct sockaddr*)dst, sizeof(*dst));

            printf(" meassage: %s\n",buf);
            printf(" success to send message, wait for  service \n");
            ssize_t _s = recvfrom(fd, buf, sizeof(buf) - 1, 0 ,\
                    (struct sockaddr*) &WhoSendToMe, &len);
            if( _s > 0 )
            {
                buf[_s] = 0;
                printf("[IP:%s|Port:%d]:%s\n",\
                        //线程不安全 nettoaddress
                        inet_ntoa(WhoSendToMe.sin_addr),\
                       ntohs(WhoSendToMe.sin_port), buf);
            }

        }
    }
}
int main(int argc, char* argv[])
{
    if( argc != 3 )
    {
        printf("usage: %s IP port \n",argv[0]);
        return 1;
    }
    int client_fd= socket(AF_INET, SOCK_DGRAM, 0);
    if( client_fd < 0 )
    {
        printf("create socket error \n");
        return -1;
    }
    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(argv[1]);  //注意网络序转换
    /*ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换*/
    ser_addr.sin_port = htons(atoi(argv[2]));  //注意网络序转换
    /*ser_addr.sin_port = htons(atoi(argv[2]));*/
    /*ser_addr.sin_addr.s_addr  = inet_addr(argv[1]);*/
    udp_msg_sender(client_fd, (struct sockaddr*) &ser_addr);
    close(client_fd);
    return 0;
}
