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
int startUp(char* port)
{
  struct sockaddr_in locate;
  locate.sin_family = AF_INET;
  locate.sin_addr.s_addr = htonl(INADDR_ANY);
  locate.sin_port = htons(atoi(port));
  int listen_sock = socket(AF_INET,SOCK_STREAM,0);
  if(bind(listen_sock,(struct sockaddr*)&locate,sizeof(locate)) < 0)
  {
    perror("bind:");
  }
  if(listen(listen_sock,2) < 0)
  {
    perror("listen");
  }

  return listen_sock;
}
void SetNoBlock(int fd)
{
  int fdBitMap = fcntl(fd,F_GETFL);
  if(fdBitMap < 0)
  {
    perror("fcntl");
    return;
  }
  fcntl(fd,F_SETFL,fdBitMap|O_NONBLOCK);
}
typedef struct buffer_info {
  int fd;
  char* buf;
  int size;
  int capacity;
} Buffer;
struct epoll_event SetEvent(int fd,int MODEL,int buf_capacity)
{
  struct epoll_event ev;
  ev.events = MODEL| EPOLLET; 
  Buffer* buf_info= (Buffer*)malloc(sizeof(Buffer)); 
  buf_info->size = 0;
  buf_info->fd = fd;
  buf_info->capacity = buf_capacity;
  buf_info->buf = (char*) malloc(sizeof(char) * buf_info->capacity);
  ev.events = EPOLLIN;
  ev.data.ptr =(void*) buf_info;   
  return ev;
}
void ProcessConnect(int efd,int listen_sock)
{
    struct sockaddr_in clinet;
    socklen_t sockaddr_len = sizeof(clinet);
    sleep(2);
    int sock = accept(listen_sock,(struct sockaddr*)&clinet,(socklen_t*)&sockaddr_len);
    if(sock< 0)
    {
      printf(" pid : %d accept error!! because of ThunderingHerd!! \n",getpid());
    }
    close(sock);
    exit(1);
}
void  service(int efd,struct epoll_event* evs,int length,int listen_sock)
{
  int i = 0;
  for(; i < length; i ++)
  {
     Buffer* buf_info = (Buffer*) evs[i].data.ptr;
    if(evs[i].events & EPOLLIN)
    {
      if(buf_info->fd == listen_sock)
      {
        ProcessConnect(efd,listen_sock);
      }
    }
  }
}
void StartToEpoll(int efd,int listen_sock)
{
  struct epoll_event evs[10];
  int evs_length = sizeof(evs)/sizeof(evs[0]);
  int pid = getpid();
  printf("pid: %d im waitting for epoll \n",pid);
  while(1)
  {
    
    int size;
    switch(size = epoll_wait(efd,evs,evs_length,-1))
    {
      case 0:
             printf("time out");
             break;
      case -1:
             printf("wait error\n");
             break;
      default:
             printf("pid : %d epoll successfully , i will quit\n",pid);
             service(efd,evs,size,listen_sock);
             break;
    }
  }
}
int main(int argc,char* argv[])
{
  if(argc != 2)
  {
    printf("usge: %s Port\n",argv[0]);
    return 1;
  }
  int listen_sock = startUp(argv[1]);
  SetNoBlock(listen_sock);
  int efd =  epoll_create(1024);
  struct epoll_event ev  = SetEvent(listen_sock,EPOLLIN,1);
  epoll_ctl(efd,EPOLL_CTL_ADD, listen_sock,&ev);
  int i = 0;
  int pid ;
  for(; i < 2; i ++)
  {
    pid = fork();
    if(pid == 0)
    {
      StartToEpoll(efd,listen_sock);
    }
    // pid < 0
  }
  int status;
  int exit_pid;
  while(( exit_pid = wait(&status)) >0)
  {
    printf("father say : %d exit normally\n",exit_pid);
  }
  printf("father say : all the process exited, i quit\n");
}
