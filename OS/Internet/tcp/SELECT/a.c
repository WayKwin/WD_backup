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
    //源数据  //  1 2 3   max :4  close(2);  max : 4
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
    // connect 来了
        //建立连接的客户端有消息了
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int sock = accept(array[0],(struct sockaddr*)&client,&len);
        //万一它只建立连接,不去向服务器发送数据,在这里立刻读
        //服务器会陷入阻塞
        //只有在下次select监测到它有数据再处理
        AddArray(array,length,sock);
  }
  else
  {
    int i = 1;
    for( ; i < length; i++ )
    {
      //?
      if(array[i] != -1 &&FD_ISSET(array[i],set))
      {
        //找到了一个正在连接的客户端
        char buf[1024] = {0};
        //  返回其他被置为0  可读的位被置为1
        int ret = read(array[i],buf,sizeof(buf) - 1);
        if( ret > 0 )
        {
          buf[ret] = 0;
          printf(" client say: %s\n", buf);
        }
        else if( ret == 0 )
        {
          printf("client quit \n");
          array[i] = INIT;
          close(array[i]);
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
  fd_set read_fds;
  // read_fds 128个字节
  int fd_array[1024];
  int array_size = sizeof(fd_array)/ sizeof(int);
  InitArray(fd_array,array_size);
  while(1)
  {
    int max_fd = listen_sock;
    ReloadArray(fd_array,array_size,&read_fds,listen_sock,&max_fd);
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
        service(fd_array,array_size,&read_fds);
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
