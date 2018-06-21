#include"http_conn.h"
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
int main()
{
  HttpConnec hc;
  hc.init();
  int listen_sock = startup(); 
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
        hc.m_sockfd = clinet_sock;
        hc.read();
        hc.parse_request();
    }
  

}
