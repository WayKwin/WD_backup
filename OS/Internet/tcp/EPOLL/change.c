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
//工作在et模式下
//所有文件描述符都必须变为 非阻塞

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
void ProcesConnect(int efd,int listen_sock)
{
  //循环读取连接直到读完
  while(1)
  {
    struct sockaddr_in clinet;
    socklen_t sockaddr_len = sizeof(clinet);
    int sock = accept(listen_sock,(struct sockaddr*)&clinet,(socklen_t*)&sockaddr_len);
    if(sock< 0)
      break;
    char IPBuf[20];
    inet_ntop(AF_INET, (const void *)&clinet.sin_addr, \
             IPBuf,sizeof(IPBuf));
    int port = ntohs(clinet.sin_port);

    printf("new connection established :[%s|%d]\n",IPBuf,port);
    SetNoBlock(sock);
    struct epoll_event ev = SetEvent(sock,EPOLLIN,1024); 
    printf(" connection sock fd : %d\n",sock);
    epoll_ctl(efd,EPOLL_CTL_ADD, sock,&ev);
  }
}
ssize_t ReadNoBlock(Buffer* buf_info)
{
  /*printf(" frist read fd: %d",buf_info->fd);*/
  int total_read = 0;
  char* buffer = buf_info->buf;
  int fd = buf_info->fd;
  int capacity = buf_info->capacity;

  while(1)
  {
    ssize_t ret = read(fd,buffer+total_read,capacity-total_read - 1);  
     total_read += ret;
     //大于capacity就越界了
     //读不满就表明读完了
     if(ret < capacity-total_read -1 )
     {
       break;
     }
  }
  return total_read;
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
        ProcesConnect(efd,listen_sock);
      }
      else 
      {
        /*printf("start read fd %d\n",buf_info->fd);*/
        int total_read = ReadNoBlock(buf_info);
        if(total_read == 0)
        {
          //关闭
          printf(" the closing fd : %d\n",buf_info->fd);
          int ret =epoll_ctl(efd,EPOLL_CTL_DEL,buf_info->fd,NULL);
         //记得关闭文件描述符!
          close(buf_info->fd);
          free(buf_info->buf);
          free(buf_info);
          printf("client quit \n");
          if(ret < 0)
              perror("delete fd fail :");
        }
        else if(total_read  < 0)
        {
          //读出错误
         printf("read fail \n");
         int ret =epoll_ctl(efd,EPOLL_CTL_DEL,buf_info->fd,NULL);
         //记得关闭文件描述符!
         close(buf_info->fd);
         free(buf_info->buf);
         free(buf_info);
         if(ret < 0)
             perror("delete fd fail :");

        }
        else if( total_read > 0 ) 
        {
          buf_info->buf[total_read] = 0;
          printf("client say: %s\n",buf_info->buf);
          int eves = EPOLLIN | EPOLLOUT | EPOLLET;
          struct epoll_event ev =  SetEvent(buf_info->fd,eves,1024);
          epoll_ctl(efd,EPOLL_CTL_MOD, buf_info->fd,&ev);
        }
      }
    }
    if(evs[i].events & EPOLLOUT)
    {
      //写事件
      
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
  struct epoll_event evs[10];
  int evs_length = sizeof(evs)/sizeof(evs[0]);
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
             service(efd,evs,size,listen_sock);
             break;

    }
  }
}
