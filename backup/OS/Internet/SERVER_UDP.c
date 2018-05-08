#include<stdio.h>
//atoi
#include<stdlib.h>
// close
#include<unistd.h>
#include<sys/socket.h>
// inet_addr
#include<netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<string.h>
#define SERVER_PORT 8888
#define BUFF_LEN 1024
int main(int argc, char* argv[])
{
    /*if( argc != 3 )*/
    /*{*/
        /*printf("usage: %s, IP Address, Port\n",argv[1]);*/
        /*return 1;*/
    /*}*/
    //协议地址格式
    struct sockaddr_in ser_addr;
    //创建socket文件. 返回文件描述符
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( server_fd <  0)
    {
        printf("create socket error\n");
        return 1;
    }
    //标识地址是 IPv4
    ser_addr.sin_family = AF_INET;
    //地址格式中的端口号
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
    ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换
    //地址格式中的Ip地址
    //注意人输入的是点分十进制,使用inet_addr 将
    //字符串中的点分十进制转换为4字节无符号数
    if( bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr))
        < 0 )
    {
        printf("socket bind fail \n");
        return -1;
    }
    char buf[BUFF_LEN];
    socklen_t len;
    struct sockaddr_in client_addr;
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        len = sizeof(client_addr);
        printf("wait  client \n");
        ssize_t count = recvfrom(server_fd, buf, sizeof(buf) - 1, 0, \
                //获取发送方的信息, 输入型参数
                //在传入socket地址时 永远记得传入的是地址类型和长度
                (struct sockaddr*)&client_addr,&len);
        if( count > 0 )
        {
            buf[count] = 0;
            printf("[IP:%s|Port:%d]: %s\n", inet_ntoa(client_addr.sin_addr), \
                    ntohs(client_addr.sin_port), buf);
            // 传入 socket文件 和发送buf, 以及发送buf长度,0 表示阻塞式等待, 发送目的地址,发送目的地址的长度
            printf(" plase enter #");
            fflush(stdout);
            ssize_t _s = read(0, buf, sizeof(buf) - 1);
            {
                if ( _s > 0 )
                {
                    buf[_s] = 0;
                    sendto(server_fd, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, len);
                    printf(" meassage: %s\n",buf);
                    printf(" success to send message, wait for  client \n");
                }
            }
        }
    }
    close(server_fd);
    return 0;
}
