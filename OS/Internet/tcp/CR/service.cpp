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
#include<list>

#define USER_LIMIT 5
#define BUFFER_SIZE 1024 
#define FD_LIMIT 65535

using namespace::std;
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
ssize_t ReadNonBlock(int fd,char buffer[])
{
  int total_read = 0;
  while(1)
  {
    int ret = read(fd,buffer+total_read,BUFFER_SIZE-total_read - 1);  
     total_read += ret;
     //大于capacity就越界了?
     if(ret <  BUFFER_SIZE-total_read - 1)
     {
       break;
     }
     printf("ret %d",ret);
  }
  return total_read;
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
  ev.events = EPOLLIN | EPOLLET;
  epoll_ctl(efd,EPOLL_CTL_ADD,listen_sock,&ev);
  // evs数组
  struct epoll_event evs[USER_LIMIT] ;
  memset(users,0,sizeof(evs));
  
  list<int> client_list; 
#if 1
  while(1)
  {
      int ret = epoll_wait(efd,evs,USER_LIMIT,-1);     
      printf(" 就绪事件个数:%d\n",ret);
      if(ret < 0)
      {
        perror("epoll error:");
        break;
      }
      for( int i = 0; i < ret ; i++ )
      {
        if( evs[i].events & EPOLLIN)
        {
          if( evs[i].data.fd == listen_sock  )
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
              printf(" 连接文件描述符 %d",connfd);
              if(client_list.size()>= USER_LIMIT)
              {
                printf("在线聊天室已满\n");
                close(connfd);
                break;
                /*continue;*/
              }
              client_list.push_back(connfd);
              SetNonBlockingFd(connfd);
              users[connfd].address = client_address;
              struct epoll_event ev;
              ev.data.fd = connfd;
              ev.events = EPOLLIN | EPOLLET|EPOLLRDHUP|EPOLLERR;
              epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&ev);
              printf("comes a new user, now have %lu users\n",client_list.size());
            }
          }
          else 
          {
             int connfd = evs[i].data.fd;
             memset(users[connfd].buf,0,sizeof(users[0].buf));
             int ret = 0;
              ret = ReadNonBlock(connfd,users[connfd].buf);
              if(ret == 0)
              {
                //关闭连接了 
                 memset(&users[evs[i].data.fd],0,sizeof(evs[i]));
                 epoll_ctl(efd,EPOLL_CTL_DEL,evs[i].data.fd,NULL);
                 close(evs[i].data.fd);   
                 client_list.remove(evs[i].data.fd);
                 //如果错误,退出的时候应该打印两次提示
                 printf("a client quit,lfet %lu\n",client_list.size());
                 break;
             }
              if(ret < 0)
              {
                printf( "ret < 0\n");
                break;
              }
              users[connfd].buf[ret] = 0;
              printf("client say: %s\n,ret : %d",users[connfd].buf,ret);
             auto iter = client_list.begin();
            //遍历注册事件的数组
            for(;  iter != client_list.begin();iter++ )
            {
              if(*iter== connfd)
              {
                continue;
              }
              
              //强制向其他的事件注册 out打开
              struct epoll_event ev;
              memset(&ev,0,sizeof(ev));
              ev.events |= ~EPOLLIN;
              ev.events |= EPOLLOUT;

              epoll_ctl(efd,EPOLL_CTL_MOD,*iter,&ev);
              // 群发消息, eves[i] 的fd是发送方
              users[*iter].write_buf = users[evs[i].data.fd].buf;
            }
         }
        }
        if(evs[i].events & EPOLLERR) 
        { 
          printf("get an error from %d \n",evs[i].data.fd);
        }       
        if(evs[i].events & EPOLLRDHUP)
       {
         //对端关闭sock文件描述符
         memset(&users[evs[i].data.fd],0,sizeof(evs[i]));
         epoll_ctl(efd,EPOLL_CTL_DEL,evs[i].data.fd,NULL);
         close(evs[i].data.fd);          
         client_list.remove(evs[i].data.fd);
         printf("a client quit,left %lu\n",client_list.size());
       }
       if(evs[i].events & EPOLLOUT)
       {
          int connfd = evs[i].data.fd;   
          int ret;
          while(1)
          {
            ret = send(connfd,users[connfd].write_buf,strlen(users[connfd].write_buf),0);
            if(ret < 0)
              break;
          }
          users[connfd].write_buf = NULL;
          evs[i].events |= ~EPOLLOUT;
          evs[i].events |= EPOLLIN;
          epoll_ctl(efd,EPOLL_CTL_MOD,connfd,&ev);
       }
      }
  }
#endif
  delete[] users;
  close(listen_sock);
  close(efd);
  return 0;
}
