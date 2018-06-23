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
extern int addfd( int epollfd, int fd, bool one_shot );
extern int removefd( int epollfd, int fd );

void addsig(int sig,void(handler)(int),bool restart = true)
{
  struct sigaction sa;
  memset(&sa,0,sizeof(sa));
  sa.sa_handler = handler;
  if(restart)
  {
    sa.sa_flags |= SA_RESTART;
  }
  sigfillset(&sa.sa_mask);
  assert(sigaction(sig,&sa,NULL) != -1);
}

int main()
{
  addsig(SIGPIPE,SIG_IGN);

  
  int listen_sock = startup(); 
    while(1)
    {
        struct sockaddr_in clinet_addr;
        socklen_t len = sizeof(clinet_addr);
        int clinet_sock = accept(listen_sock, \
                (struct sockaddr*)&clinet_addr, &len);
        
        if( clinet_sock < 0 )
        {
            printf(" accept error \n");
            break;
            continue;
        }
        //
    }
    return 0;
}
