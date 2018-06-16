#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<assert.h>

#define BUFFER_SIZE 1024
void SetNonBlockingFd(int fd)
{
  int old_options = fcntl(fd,F_GETFL);
  fcntl(fd,F_SETFL,old_options | O_NONBLOCK);
}
int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    //basename 从文件名中剥去目录和后缀
    printf("usge : %s ip_address port_number\n",basename(argv[0]));
    return 1;
  }
  const char* ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in service_address;
  memset(&service_address,0,sizeof(service_address));
  service_address.sin_family = AF_INET;
  service_address.sin_port = htons(port);
  inet_pton(AF_INET,ip,&service_address.sin_addr);

  //对于我这种菜鸟来说,PF和AF没啥区别...
  //linux下也是这么定义的
  //bits/socket.h:99:#define        AF_INET         PF_INET 
  int sockfd = socket(PF_INET,SOCK_STREAM,0);
  
  assert(sockfd >= 0);
  
  if(connect(sockfd,(struct sockaddr*) &service_address,sizeof(service_address)) < 0)
  {
    close(sockfd);
    printf("connect error \n");
    exit(1);
  }

  int efd = epoll_create(2);
  struct epoll_event evs[2];
  evs[0].data.fd = 0;
  evs[0].events = EPOLLIN;
  
  evs[1].data.fd = sockfd;
  evs[1].events = EPOLLIN | EPOLLRDHUP;

  epoll_ctl(efd,EPOLL_CTL_ADD,0,&evs[0]);
  epoll_ctl(efd,EPOLL_CTL_ADD,sockfd,&evs[1]);

  SetNonBlockingFd(sockfd);
  
  memset(&evs,0,sizeof(evs)); 

  while(1)
  {
     int ret = epoll_wait(efd,evs,2,-1);
      if(ret < 0)
      {
        printf("epoll fail\n");
        break;
      }
      printf("就绪事件个数%d \n",ret);
      void service(struct epoll_event* evs,int length,int sockfd);

      service(evs,2,sockfd);
  }
  close(sockfd);
}
void service(struct epoll_event* evs,int length,int sockfd)
{
  char  read_buf[BUFFER_SIZE];
  char  write_buf[BUFFER_SIZE];
  int i = 0;
  int pipefd[2];
  int ret = pipe(pipefd);
  assert(ret != -1);
  for(; i < length; i++)
  {
    if(evs[i].events & EPOLLRDHUP)
    {
      printf("service close the connection\n");
      continue;
    }
    if(evs[i].events & EPOLLIN )
    {
      printf("in 文件描述符 %d\n",evs[i].data.fd);
      if(evs[i].data.fd == 0)
      {
         printf("please enter :");
         fflush(stdout);
         read(0,write_buf,sizeof(write_buf) - 1);
         write(sockfd,write_buf,sizeof(write_buf) - 1);
         //int size = splice(0,NULL,pipefd[1],NULL,BUFSIZ,SPLICE_F_MORE | SPLICE_F_MOVE); 
         //size = splice(pipefd[0],NULL,sockfd,NULL,BUFSIZ,SPLICE_F_MORE | SPLICE_F_MOVE); 
         //if(size < 0)
         //{
           //perror("splice:");
         //}
      }
     if(evs[i].data.fd == sockfd)
      {
        printf("in 文件描述符 %d\n",evs[i].data.fd);
        read_buf[0] = 0;
        int size;
        size  =recv(sockfd,read_buf,sizeof(read_buf) - 1,0);
        read_buf[size] =  0; 
        printf("%s",read_buf);
      }
    }
  }
}

