#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/select.h>
// -1 文件描述符不可能出现
#define INIT -1
int  startup();
void InitArray(int array[],int length)
{
  if( array == NULL || length < 0 )
    return;
  int i = 0;
  for(; i < length; i++ )
  {
    array[i] = INIT;
  }
}
void ReloadArray(int array[],int length,fd_set* read_fds, int listen_sock,int *max_fd)
{
  array[0] = listen_sock;
  //清空文件描述符集
  FD_ZERO(read_fds);
  FD_SET(listen_sock,read_fds);
  int i;
  for( i = 1; i < length; i++ )
  {
    if( array[i] != INIT )
    {
      FD_SET(array[i],read_fds);
      if( array[i] > *max_fd )
      {
        *max_fd = array[i];
      }
    
    }
  }
}
void AddArray(int array[],int length,int fd)
{
  int  i = 1;
  for( ; i < length; i++ )
  {
    if( array[i] == -1 )
    {
      array[i] = fd;
      break;
    }
  }
}
void service(int array[], int length, fd_set* set)
{

  if( FD_ISSET(array[0],set) )
  {
    // connect 来了就将其关闭
        //建立连接的客户端有消息了
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        //必定不会阻塞在这里
        int sock = accept(array[0],(struct sockaddr*)&client,&len);
        if( sock < 0 )
        {
          printf(" accept error \n");
        }
        close(sock);
        exit(1);
  }
}
void StartToSelect(int listen_sock,int * fd_array,int array_size,fd_set read_fds)
{
  int pid = getpid();
  printf("pid: %d im waitting for select \n",pid);
  while(1)
  {
    int max_fd = listen_sock;
    ReloadArray(fd_array,array_size,&read_fds,listen_sock,&max_fd);
    //阻塞在select上会发生惊群
    int ret = select(max_fd + 1,&read_fds, NULL, NULL,NULL); 
    switch(ret)
    {
      case 0 :
        printf("select timeout\n");
        break;
      case  -1:
        printf("select error \n");
        break;
      default:
        printf("pid : %d select successfully , i will quit\n",pid);
        service(fd_array,array_size,&read_fds);
        break;
    }
  }

}
int main(int argc,char* argv[])
{
  if( argc !=2 )
  {
    printf(" usage: %s  port \n",argv[0]);
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
  fd_set read_fds;
  // read_fds 128个字节
  int fd_array[1024];
  int array_size = sizeof(fd_array)/ sizeof(int);
  InitArray(fd_array,array_size);
  int i = 0;
  int pid ;
  for(; i < 2; i ++)
  {
    pid = fork();
    if(pid == 0)
    {
      StartToSelect(listen_sock,fd_array,array_size,read_fds);
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
