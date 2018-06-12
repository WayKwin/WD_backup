#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<poll.h>
// -1 文件描述符不可能出现
#define INIT -1

typedef struct pollfd pollfd;
void InitPoll(pollfd* fd_list,int size,int listen_sock)
{
  fd_list[0].fd = listen_sock;
  fd_list[0].events = POLLIN;
  int i ;
  for(i = 1 ; i < size; i++)
  {
    fd_list[i].fd = INIT;
    fd_list[i].events = 0;
    fd_list[i].revents =0; 
  }
}
void AddPoll(pollfd* fd_list,int size,int fd)
{
  int i ;
  for(i = 1 ; i < size; i++)
  {
    if( fd_list[i].fd & INIT)
    {
      fd_list[i].fd = fd;
      fd_list[i].events = POLLIN;
      break;
    }
  }
}
void service(pollfd* fd_list, int size)
{
  if( fd_list[0].revents & POLLIN  )
  {
    // connect 来了
        //建立连接的客户端有消息了
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int sock = accept(fd_list[0].fd,(struct sockaddr*)&client,&len);
        AddPoll(fd_list,size,sock);
  }
  else
  {
    int i = 1;
    for( ; i < size; i++ )
    {
      //?
      if(fd_list[i].fd != -1 &&fd_list[i].revents&POLLIN)
      {
        //找到了一个正在连接的客户端
        char buf[1024] = {0};
        //  返回其他被置为0  可读的位被置为1
        int ret = read(fd_list[i].fd,buf,sizeof(buf) - 1);
        if( ret > 0 )
        {
          buf[ret] = 0;
          printf(" client say: %s\n", buf);
        }
        else if( ret == 0 )
        {
          printf("client quit \n");
          close(fd_list[i].fd);
          fd_list[i].fd = INIT;
        }
        else if( ret < 0 )
        {
          printf("read error\n");
        }
      }
    }
  }
}
int main(int argc,char* argv[])
{
  if( argc !=2 )
  {
    printf(" usage: %s  port > 1024",argv[0]);
    return 0;
  }
  //创建tcp连接
  struct sockaddr_in locate;
  locate.sin_family = AF_INET;
  locate.sin_port = htons(atoi(argv[1]));
  locate.sin_addr.s_addr = htonl(INADDR_ANY);
  int listen_sock = socket(AF_INET,SOCK_STREAM,0); 
  if(bind(listen_sock,(struct sockaddr* )&locate,sizeof(locate)) < 0) 
  {
    perror("bind error: \n");
    return 2;
  }
  if(listen(listen_sock,2) != 0)
  {
    printf("listen error\n");
    return 4;
  }
  pollfd fd_array[1024];
  int array_size = sizeof(fd_array)/ sizeof(fd_array[0]);
  InitPoll(fd_array,array_size,listen_sock);
  AddPoll(fd_array,array_size,listen_sock);
  while(1)
  {
    int ret = poll(fd_array,array_size,1000);
    switch(ret)
    {
      case 0 :
        printf("poll timeout\n");
        break;
      case  -1:
        printf("poll error \n");
        break;
      default:
        service(fd_array,array_size);
        break;
    }
    // 将监听套接字加入 read_fds ,并且加入到数组中
    // 开始select
    // 如果是监听套接字, 接受请求,建立连接,同时把新的套接字加入数组中
    // 
    // 如果是连接套接字,处理数据
    // 
    // 循环一次,就应该重新设置
  }

}
