#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<assert.h>
#include<memory>

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535
//照着书上 直接简单粗暴创建FD_limt的文件描述符
//自己设想 将每个结构体接到 events.data的(void*)ptr上
struct client_data
{
  struct sockaddr_in address;
  char* write_buf;
  char buf[BUFFER_SIZE];
};
void SetNonBlockingFd(int fd)
{
  int old_options = fcntl(fd,F_GETFL);
  fcntl(fd,F_SETFL,old_options | O_NONBLOCK);
}
int main(int argc,char* argv[])
{
  if(argc != 2)
  {
    //basename 从文件名中剥去目录和后缀
    printf("usge : %s port_number\n",argv[0]);
    return 1;
  }
  int port = atoi(argv[1]);

  struct sockaddr_in service_address;
  memset(&service_address,0,sizeof(service_address));
  service_address.sin_family = AF_INET;
  service_address.sin_port = htons(port);
  service_address.sin_addr.s_addr = htonl(INADDR_ANY);

  //bits/socket.h:99:#define        AF_INET         PF_INET 
  int listen_sock = socket(PF_INET,SOCK_STREAM,0);
  assert(listen_sock >= 0);
  int on = 1; 
  setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  if(bind(listen_sock,(struct sockaddr*)&service_address,sizeof(service_address)) < 0 )
  {
    perror("bind error:");
    exit(1);
  }
  int ret= listen(listen_sock,5);
  SetNonBlockingFd(listen_sock);
  if(ret < 0)
  {
    perror("bind error:");
    return 1;
  }
  int efd;
  if(( efd = epoll_create(1024 )) < 0)
  {
    perror("epoll_create:");
    return 1;
  }

  //users数组
  struct client_data* users = new client_data[FD_LIMIT]; 
  memset(users,0,sizeof(client_data)*FD_LIMIT);

  struct epoll_event ev;
  ev.data.fd = listen_sock;
  ev.events = EPOLLIN | EPOLLIN;
  epoll_ctl(efd,EPOLL_CTL_ADD,listen_sock,&ev);
  // evs数组
  struct epoll_event evs[USER_LIMIT] ;
  memset(users,0,sizeof(evs));

  int connectNumber = 0;
  while(1)
  {
      int ret = epoll_wait(efd,evs,USER_LIMIT,-1);     
      printf(" 就绪事件 %d \n",ret);
      if(ret < 0)
      {
        perror("epoll error:");
        break;
      }
      for( int i = 0; i < ret ; i++ )
      {
        if(( evs[i].data.fd == listen_sock  )&& ( evs[i].events & POLL_IN ))
        {
          struct sockaddr_in client_address;
          socklen_t client_addrlength = sizeof(client_address);
          while(1)
          {
            //非阻塞读取
            int connfd = accept(listen_sock,(struct sockaddr*)&client_address,&client_addrlength);
            if(connfd < 0)
            {
                break;
            }
            if(connectNumber >= USER_LIMIT)
            {
              printf("在线聊天室已满\n");
              close(connfd);
              break;
              /*continue;*/
            }
            connectNumber++;
            SetNonBlockingFd(connfd);
            users[connfd].address = client_address;
            struct epoll_event ev;
            ev.data.fd = listen_sock;
            ev.events = EPOLLIN | EPOLLET|EPOLLRDHUP|EPOLLERR;

            epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&ev);
            printf("comes a new user, now have %d users\n",connectNumber);
          }
          
        }
       else if(evs[i].events & EPOLLERR) 
        { 
          printf("get an error from %d \n",evs[i].data.fd);
        }       
       else if(evs[i].events & EPOLLRDHUP)
       {
         //对端关闭sock文件描述符
         memset(&users[evs[i].data.fd],0,sizeof(evs[i]));
         epoll_ctl(efd,EPOLL_CTL_DEL,evs[i].data.fd,NULL);
         close(evs[i].data.fd);          
         connectNumber--;
         printf("a client quit,left %d\n",connectNumber);
       }
       else if(evs[i].events & EPOLLIN)
       {
         int connfd = evs[i].data.fd;
         memset(users[connfd].buf,0,sizeof(users[0].buf));
         int ret;
         while(1)
         {
          ret = recv(connfd,users[connfd].buf,BUFFER_SIZE - 1,0); 
          if(ret < 0)
          {
            //非阻塞读完了
              break;
          }
          else if(ret == 0)
          {
            //关闭连接了 
             memset(&users[evs[i].data.fd],0,sizeof(evs[i]));
             epoll_ctl(efd,EPOLL_CTL_DEL,evs[i].data.fd,NULL);
             close(evs[i].data.fd);   
             connectNumber--;
             //如果错误,退出的时候应该打印两次提示
             printf("a client quit,lfet %d\n",connectNumber);
             break;
          }
         }
         if(!ret)
         {
           continue; 
         }
        int j = 0;
        //遍历注册事件的数组
        for(; j < USER_LIMIT ;j++ )
        {
          if(evs[i].data.fd == connfd)
          {
            continue;
          }
          //强制向其他的事件注册 out打开
          evs[j].events |= ~EPOLLIN;
          evs[j].events |= EPOLLOUT;
          users[evs[j].data.fd].write_buf = users[evs[j].data.fd].buf;
        }
       }
       else if(evs[i].events & EPOLLOUT)
       {
          int connfd = evs[i].data.fd;   
          int ret;
          while(1)
          {
            ret = send(connfd,users[connfd].write_buf,strlen(users[connfd].write_buf),0);
            users[connfd].write_buf = NULL;
            evs[i].events |= ~EPOLLOUT;
            evs[i].events |= EPOLLIN;
          }
       }
      }
  }
  delete[] users;
  close(listen_sock);
  close(efd);
  return 0;
}
