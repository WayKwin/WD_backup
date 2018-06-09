#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#define BUFF_SIZE 1024 
#define PORT 8080
int startup()
{
  int sock = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in service;
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = htonl(INADDR_ANY);
  service.sin_port = htons(PORT); 
  //快速重启
  //注意在bind之前
  int on = 1;
  setsockopt(sock,SOL_SOCKET,SO_REUSEADDR, &on,sizeof(on));
  if(bind(sock,(struct sockaddr*)&service,sizeof(service)) < 0 )
  {
    perror("bind error:");
    exit(1);
  }
  int ret = listen(sock,2);
  if(ret < 0)
  {
    perror("listen error");
    exit(1);
  }
  return sock;

}
int get_line(int sock,char buf[],int length)
{
  char c = 'a';
  int i = 0;
  int ret;
  while((ret = recv(sock,&c,1,0))> 0 && i < length - 1)
  {
    if(c == '\n')
    {
      buf[i++] = c;
      break;
    }
    else if( c == '\r' )
    {
      if(recv(sock,&c,1,MSG_PEEK)  > 0)
      {
         if(c == '\n') 
           recv(sock,&c,1,0);
      }
      c = '\n';
      buf[i++] = c;
      break;
    }
    buf[i++] = c;
  }
  if(ret < 0)
  {
      return ret;
  }
  return i;
}
void deal_msg(int sock)
{
  char buf[BUFF_SIZE]; 
  while(1)
  {
    int ret = get_line(sock,buf,sizeof(buf));
    if( ret <= 0)
      break;
    buf[ret] = 0;
    printf("%s",buf);
  }
  exit(1);
}
void deal_sock(int sock, struct sockaddr_in* clinet_addr,int listen_sock)
{
  int pid  = fork();
  if(pid == 0)
  {
    close(listen_sock);
    pid = fork();
    if(pid > 0 )
      exit(0);
    else 
      deal_msg(sock);
  }
  else
  {
    close(sock);
    wait(NULL);
  }
}
int main()
{
  int listen_sock = startup();
  printf("listen_sock : %d\n",listen_sock);
    while(1)
    {
        struct sockaddr_in clinet_addr;
        socklen_t len = sizeof(clinet_addr);
        //一旦有建立连接完成的 套接字,就为其开辟进程
        int clinet_sock = accept(listen_sock, \
                (struct sockaddr*)&clinet_addr, &len);
        if( clinet_sock < 0 )
        {
            printf(" accept error \n");
            break;
            continue;
        }
        //传入listen_sock 是为了子进程关闭
        deal_sock(clinet_sock, &clinet_addr,listen_sock);
    }
}
