#include"service.h"
//注意一定要把文件描述符设置为非阻塞!!!
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
int ClearRequest(int sock)
{

  char buf[BUFF_SIZE];
  int ret = 0;
  while(1)
  {
    //getline应该是非阻塞版本的
    ret = get_line(sock,buf,sizeof(buf));
    if( ret <= 0)
      break;
    printf("%s",buf);
  }
  return ret;
}
int ClearHeader(int sock)
{
  char buf[BUFF_SIZE];
  int ret = 0;
  while(strcmp(buf,"\n") != 0)
  {
    ret = get_line(sock,buf,sizeof(buf));
    printf("%s",buf);
    fflush(stdout);
  }
  return 1;
}
int Deal_Header(char* buf,int sock)
{
  /*char* method = NULL;*/
  /*char* RequestPath = NULL;*/
  /*char* HttpVersion = NULL;*/
  //错误,这里header[0] 改变了,但是method不会改变, 改变method的指向得它的地址
  //错误码
  int ErrorCode = 200;
  char* header[3] ;

  //获取请求资源信息
  struct stat file_stat;

  //抽取内容所需
  int count = 0;
  int i = 0; 
  int Space_status = 0;

  for(; buf[i] != '\0'; i++)
  {
   if(!isspace(buf[i]) && Space_status == 0) 
   {
      header[count++] = buf + i;
      Space_status = 1;
   }
   else if(isspace(buf[i]))
   {
     Space_status = 0;
     buf[i] = '\0';
   }
  }
  char method[BUFF_SIZE >> 3];
  strcpy(method,header[0]);
  
  char RequestPath[BUFF_SIZE >> 3];
  strcpy(RequestPath,header[1]);
  /*char* HttpVersion = header[2];*/
#ifdef DEBUG
  printf("method:%s\n",method);
  printf("RequestPath:%s\n",RequestPath);
  /*printf("HttpVersion:%s\n",HttpVersion);*/
#endif
  //处理method
  int cgi_flag = 0;
  char* RequestParameters;
  //请求应该,4忽略大小写的
  if(strcasecmp(method,"GET") == 0)
  {
   for(i = 0; RequestPath[i] != '\0'; i++)
   {
     if(RequestPath[i] == '?')
     {
       //请求参数在 ? 以后
       cgi_flag = 1;
       RequestPath[i++] = '\0';
       RequestParameters = RequestPath + i;
       break;
     }
   }
   //从这里结束 是普通cgi
  }
  else if(strcasecmp(method,"POST") == 0)
  {
    cgi_flag = 1;
    //请求参数在正文
    //从正文读取
  }

  //处理请求资源
  if(cgi_flag == 1)
  {
    //TODO cgi
  }
  else 
  {
    // 封装函数 1. 无参get 和 有参cgi
    //记得读完请求(wrong 读完报头首部)
    ClearHeader(sock);
    //发送响应行
    char* ResponseRow = (char*)"HTTP/1.1 200 ok\n";
    write(sock,ResponseRow,strlen(ResponseRow));
    //发送响应头 TODO
    char* ResponseHeader = (char*)"Server: Waykwin\nContent-Type: text/html;\n";
    write(sock,ResponseHeader,strlen(ResponseHeader));
    
    //发送空行
    write(sock,"\n",1);

    //正文处理
    char tmpbuf[BUFF_SIZE >> 3] ;
    strcpy(tmpbuf,RequestPath);

    sprintf(RequestPath,"./WWW%s",tmpbuf);
    /*printf("RequestPath: %s\n",RequestPath);*/
    if(strcasecmp(RequestPath,"./WWW/") == 0  )
    {
      //打开index.html 发送该文件
      int index_fd = open("/home/waykwin/WorkSpace/OS/Internet/HTTP/WWW/index.html",O_RDONLY);
      if(index_fd < 0)
      {
        perror("index_fd error \n");
        ErrorCode = 404;
        goto ERROR;
      }
      //获取文件大小
      if(fstat(index_fd,&file_stat) < 0 )
      {
        perror("fstat:\n");
      }
      if(sendfile(sock,index_fd,0,file_stat.st_size)  < 0)
        perror("sendfile:");
      /*printf(" 发送完毕\n");*/
    }
    else 
    {
      //指定文件 TODO

    }
    
  }
ERROR:
  //TODO
  EchoErrorCode(ErrorCode,sock);
  return ErrorCode;
  return 1; 
  //处理http版本
}
int get_line(int sock,char buf[],int length)
{
  char c = 'a';
  int i = 0;
  int ret;
  while(( ret = recv(sock,&c,1,0)> 0  )&&i < length - 1)
  {
    if(c == '\n')
    {
      buf[i++] = c;
      break;
    }
    if( c == '\r' )
    {
      if((ret = recv(sock,&c,1,MSG_PEEK))> 0)
      {
         if(c == '\n') 
           recv(sock,&c,1,0);
      }
      c = '\n';
      buf[i++] = c;
      break;
    }
    buf[i++] = c;
  }
 if(ret <= 0)
  {
      return ret;
  }
  buf[i] = 0;
  return i;
}
int deal_msg(int sock)
{
  SetNoBlock(sock);
  char buf[BUFF_SIZE]; 
#ifdef DEBUG
  while(1)
  {
    int ret = get_line(sock,buf,sizeof(buf));
    if( ret <= 0)
      break;
    printf("%s",buf);
  }
#endif
 get_line(sock,buf,sizeof(buf));
 Deal_Header(buf,sock);

 exit(1);
}
int deal_sock(int sock, struct sockaddr_in* clinet_addr,int listen_sock)
{
  int pid  = fork();
  if(pid == 0)
  {
    close(listen_sock);
    pid = fork();
    if(pid > 0 )
      exit(0);
    else 
      deal_msg(sock);
  }
  else
  {
    close(sock);
    wait(NULL);
  }
  return 1;
}
int main()
{
  int listen_sock = startup();
  /*printf("listen_sock : %d\n",listen_sock);*/
    while(1)
    {
        struct sockaddr_in clinet_addr;
        socklen_t len = sizeof(clinet_addr);
        //一旦有建立连接完成的 套接字,就为其开辟进程
        int clinet_sock = accept(listen_sock, \
                (struct sockaddr*)&clinet_addr, &len);
        if( clinet_sock < 0 )
        {
            printf(" accept error \n");
            break;
            continue;
        }
        //传入listen_sock 是为了子进程关闭
        deal_sock(clinet_sock, &clinet_addr,listen_sock);
    }
}
