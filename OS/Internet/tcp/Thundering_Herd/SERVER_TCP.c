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
//使用sockaddr 要传入len区分协议
//直接使用sockaddr_in 不用
void deal_msg(int sock, struct sockaddr_in* clinet_addr)
{
    int port = ntohs(clinet_addr->sin_port);
    char IPBuf[20];
    IPBuf[0] = 0;
    // 注意 传入第二个参数
    inet_ntop(AF_INET, (const void *)&clinet_addr->sin_addr, \
             IPBuf,sizeof(IPBuf));
    char buf[BUFF_SIZE];
    buf[0] = 0;
    while(1)
    {
        //单进程会一直卡死在这个while(1)里 只服务一个客户端
        ssize_t s = read(sock, buf, sizeof(buf) - 1);
        if( s > 0 )
        {
            buf[s] = 0;
            //处理接收到的信息
            printf("[%s|%d] # %s\n ", IPBuf, port, buf);
        }
        if( s  == 0 )
        {
            // 客户端结束会话
            printf("[%s|%d] #  quit ! \n",IPBuf, port);
            //进程结束,记得释放它的sock文件描述符
            close(sock);
            break;
        }
        if( s < 0 )
        {
            printf("read error\n");
            continue;
        }
    }
}
void deal_sock(int sock, struct sockaddr_in* clinet_addr,int listen_sock)
{
      int pid = fork();
      if( pid ==  0)
      {
          //儿子孙子不需要监听进程
          close(listen_sock);
          pid = fork();
          {
              if ( pid > 0 )//儿子退出//给爷爷发消息
                  exit(0);
              deal_msg(sock, clinet_addr);//孙子运行,变成孤儿,结束init 1回收
              exit(0);
          }
      }
      else//爷爷等儿子
      {
          // 爷爷不需要连接套接字读写内容
          close(sock);//避免文件描述符溢出关闭不用的文件描述符
          waitpid( -1, NULL,  0);
          //这里父进程就是服务器,不能退出!
          /*exit(0);*/
      }
}
int main(int argc,char* argv[])
{
     if( argc != 3 )
     {
        printf("usage: %s  IP Port \n", argv[0]);
        return 1;
     }
     struct sockaddr_in ser_addr;
     //将 套接字地址置零 不推广这个函数请使用memset
     bzero((void *)&ser_addr,sizeof(ser_addr));
     ser_addr.sin_family = AF_INET;
     ser_addr.sin_port = htons(atoi(argv[2]));
     ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int listen_sock = socket( AF_INET, SOCK_STREAM,  0);
    if( listen_sock < 0 )
    {
        printf("socket error \n");
        return 2;
    }
    if( bind(listen_sock, (struct sockaddr*)&ser_addr,
      sizeof(ser_addr) ) < 0 )
    {
        printf("bind error \n");
        return 3;

    int ret = listen(listen_sock, 2);
    if(ret != 0)
    {
        printf("listen error \n");
        return 4;
    }
    while(1)
    {
        struct sockaddr_in clinet_addr;
        socklen_t len = sizeof(clinet_addr);
        //一旦有建立连接完成的 套接字,就为其开辟进程
        int clinet_sock = accept(listen_sock, \
                (struct sockaddr*)&clinet_addr, &len);
        printf(" connection established \n");
        if( clinet_sock < 0 )
        {
            printf(" accept error \n");
            continue;
        }
        //传入listen_sock 是为了子进程关闭
        deal_sock(clinet_sock, &clinet_addr,listen_sock);
    }

}
