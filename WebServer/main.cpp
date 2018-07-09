#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

#include"http_conn.h"
#include "threadpool.cpp"
#include"locker.h"
//#include"log.h"

#define PORT 8080
#define MAX_FD 1024
#define  MAX_EVENT_NUMBER 2048 

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
  //LogError("sigfillset");

  assert(sigaction(sig,&sa,NULL) != -1);
}

int main()
{
  addsig(SIGPIPE,SIG_IGN);
  ThreadPool<HttpConnec>* tp
    =  new ThreadPool<HttpConnec>; 

  int epollfd = epoll_create(5);
  assert(epollfd > 0);
  HttpConnec::m_epollfd = epollfd;
  //epoll就绪队列
  struct epoll_event evs [MAX_EVENT_NUMBER];
  HttpConnec* usrs = new HttpConnec[MAX_FD];

  if(usrs == NULL)
  {
    //LogError("memory full");
  }
  assert(usrs);


  int listen_sock = startup(); 
  addfd(epollfd,listen_sock,false);


    while(1)
    {
      int number = epoll_wait(epollfd,evs,MAX_EVENT_NUMBER,-1);
      // errno == EINTR 表示被中断而不是出错
      if(number < 0 && errno != EINTR)
      {
          //LogInfo("epoll wait failure");
          break;
      }
      int i = 0;
      for(; i < number; i++)
      {
        int sockfd = evs[i].data.fd;
        if(sockfd == listen_sock)
        {
          struct sockaddr_in clinet_addr;
          socklen_t len = sizeof(clinet_addr);
          int clinet_sock = accept(listen_sock, \
                  (struct sockaddr*)&clinet_addr, &len);
          assert(clinet_sock>= 0);
          if(HttpConnec::m_user_count >= MAX_FD)
          {
            //LogWarning("service busying");
            continue;
          }

          usrs[clinet_sock].init(clinet_sock,clinet_addr); 
        }
        else if(evs[i].events & (EPOLLRDHUP | EPOLLHUP|EPOLLERR))
        {
          usrs[sockfd].close_connec();
        }
        else if(evs[i].events & EPOLLIN)
        {
          usrs[sockfd].read();
          tp->SetEvents(usrs+sockfd);
        }
        else if(evs[i].events & EPOLLOUT)
        {
          if(!usrs[sockfd].write())
          {
            usrs[sockfd].close_connec();
          }
        }
      }
    }
    close(listen_sock);
    close(epollfd);
    delete [] usrs;
    return 0;
}
