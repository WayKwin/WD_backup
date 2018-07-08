#include"http_conn.h"

/*debug 1
 * oneshot 作用: 多线程,et 一个线程 A 在循环读取一个socket上的读事件,当它还没读完的时候,此时这个socket又触发了一个读事件(边沿触发)
 * 会被其他线程拿到,会就造成数据不一致的状态
 * oneshot: 在socket触发之后就会清除此socket, 只有当 线程 A 读完数据发生 EAGAIN时,再次将此socket加入epoll的监听列表中
 * 但在加入监听列表前 socket又就绪了,那么加入epoll的时候就会立刻返回,不影响
 * 
 */
/*debug 2
 *在一个返回值为bool的函数中我没有写返回值,导致函数随机
 *跳转, 错误表现为 "非法错误" ,调试了很久才发现问题所在
 * 
 * 
 * /
/*debug 2
 * 在realse版本中,我知道是需要用非阻塞读取
 * 但是在debug中我忘记将sock设置为非阻塞模式
 * 所以现象是服务器已经将数据发送给客户端,
 * 但在浏览器未接收到任何数据
 * 
 */
/*
 * 现象表明http在解析htlm文档的时候会将所需资源再次发起http请求
 * 
 * 
 * 
 * TODO
 * cgi 服务器,设想:
 * 进程池 模版参数<T,G> 对应insert和 search俩个类
 * 分别对应两个事件队列,两个信号量
 *  在append操作时,通过判断 CGI请求程序加入指定的事件队列
 *  一部分进程只能PV insert(只处理insert)
 *  另一部进程处理search
 *  (如何在两个进程之间传递文件描述符)
 * 
 */
int HttpConnec::m_epollfd;
int HttpConnec::m_user_count;
const char* ok_200_title = "OK";
const char* error_400_title = "Bad Request";
const char* error_400_form = "Your request has bad syntax or is inherently impossible to satisfy.\n";
const char* error_403_title = "Forbidden";
const char* error_403_form = "You do not have permission to get file from this server.\n";
const char* error_404_title = "Not Found";
const char* error_404_form = "The requested file was not found on this server.\n";
const char* error_500_title = "Internal Error";
const char* error_500_form = "There was an unusual problem serving the requested file.\n";
const char* DocRoot = "./www";
void SetNonBlocking(int fd)
{
  int old_status = fcntl(fd,F_GETFL); 
  int new_status = old_status | O_NONBLOCK;
  if(fcntl(fd,F_SETFL,new_status) < 0)
  {
    throw "fcntl error\n";
  }
}

void addfd(int epollfd,int fd,bool onshot)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = EPOLLIN  | EPOLLET| EPOLLRDHUP;
  if(onshot)
  {
    ev.events|= EPOLLONESHOT;
  }
 if( epoll_ctl(epollfd,EPOLL_CTL_ADD,fd ,&ev) < 0)
 {
   throw  "epoll_ctl add \n";
 }
 SetNonBlocking(fd);

}
void removefd(int epollfd,int fd)
{
    epoll_ctl( epollfd, EPOLL_CTL_DEL, fd, 0 );
    close( fd );
}
void modfd(int epollfd,int fd,int FLAG)
{
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = FLAG | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &ev );

}
// 函数
void HttpConnec::init(int sockfd,const sockaddr_in& addr)
{
  m_sockfd = sockfd;
  m_addr = addr;
  int error = 0;
  socklen_t len = sizeof( error );
  getsockopt( m_sockfd, SOL_SOCKET, SO_ERROR, &error, &len );
  int reuse = 1;
  setsockopt( m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof( reuse ) );
  addfd( m_epollfd, sockfd, true );
  m_user_count++;

  init();

}
void HttpConnec::init()
{
    // init read 
    m_handled_idx = 0;
    m_read_indx = 0;
    // stat_line = (在link_ok 后)m_handled_indx
    // 用来和handled_index 实现getline();
    m_start_line = 0;
    memset(m_read_buf,0,sizeof(m_read_buf));

    // int enum
    m_method = GET;


  //init write
  memset(m_write_buf,0,sizeof(m_read_buf));
  m_write_idx = 0;

  //头部
  m_content_length = 0;
}
void HttpConnec::close_connec(bool real_close)
{
  if (real_close && m_sockfd != -1)
  {
    removefd(m_epollfd,m_sockfd);
    m_sockfd = -1;
    m_user_count --;
  }
}
bool HttpConnec::read()
{
  // 测试的时候多次连接 m_read_indx 不会重头开始
  //  等到多线程版本, 看是否需要读完一次请求清零
  if( m_read_indx  >= READ_BUFFER_SIZE )
  {
    printf("read:read out of range \n");
    return false;
  }
  int read_count = 0;
  while(1)
  {
    read_count = recv(m_sockfd,m_read_buf + m_read_indx,READ_BUFFER_SIZE - m_read_indx,0);
    if(read_count == -1)
    {
      if(errno == EAGAIN || errno ==EWOULDBLOCK)
      {
        // 是否是oneshot 要重新添加
        //下次接着读
        printf("read over(in read function)\n");
        break;
        //continue;
      }
    }
    if( read_count == 0 )
    {
      return false;
    }
    m_read_indx += read_count;
  }
  return true;
}
HttpConnec::READ_LINE_STATUS HttpConnec::parse_line()
{
  char c = 'a';
  // m_handled_idx 指向下一个要处理的字符
  for(; m_handled_idx < m_read_indx; m_handled_idx++)
  {
    c  = m_read_buf[m_handled_idx];
    // \r\n
    if( c == '\r' )
    {
      if((m_handled_idx + 1) == m_read_indx) 
      {
        return LINE_LOCAL;
      }
      // 空行情况:  accpet_language: sadsads\r\n\r\n 
      // 最后两个\r\n 被变成\0\0 所以text里装的是\0
      else if(m_read_buf[m_handled_idx + 1] == '\n')
      {
        // \r \n 变成 \0
        m_read_buf[m_handled_idx++] = '\0';
        //跳过 \n
        m_read_buf[m_handled_idx++] = '\0';
        return LINE_OK;
      }
     // \rs
      return LINE_BAD;
    }
    // 读到 \r \n
    else if(c == '\n')
    {
            if((m_handled_idx > 1) && (m_read_buf[ m_handled_idx-1] == '\r'))
            {
                m_read_buf[m_handled_idx-1] = '\0';
                m_read_buf[m_handled_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
    }
  }
  return LINE_LOCAL;
}
HttpConnec::HTTP_CODE HttpConnec::parse_request()
{
  READ_LINE_STATUS line_status = LINE_OK;
  HTTP_CODE ret = LOCAL_REQUEST;
  m_parse_status = PARSE_LINE;
  char* text = 0;
  printf("====================\n");
  printf("以下是HTTP请求\n");
  while(if(m_start_l)( line_status = parse_line())== LINE_OK)
  {
    text = getline();
    m_start_line = m_handled_idx;
    if(text[0] == '\0')
    {
      printf("http request:空行\n");
    }
    else printf("http request:%s\n",text);

    switch(m_parse_status)
    {
      case PARSE_LINE:  
        ret = parse_request_line(text);
        if(ret == BAD_REQUEST)
          return BAD_REQUEST;
          break;
      case PARSE_HEADER:
          ret = parse_header(text);
          if(ret == OK_REQUEST)
          {
            printf("okokok\n");
            return OK_REQUEST;
          }
          break;
      case PARSE_CONTENT:
          printf("==========================================================\n");
          ret = parse_content(text);
          if(ret == OK_REQUEST)
            return OK_REQUEST;
          else if(ret == BAD_REQUEST)
            return BAD_REQUEST;
          break;
    }
  }
  return LOCAL_REQUEST;
}

HttpConnec::HTTP_CODE HttpConnec::parse_request_line(char* text)
{
  // 坑: strtok虽然方便, 但是内部用了静态变量,不适合多线程版

  //char* method =  strtok(text," ");
  //char* url =  strtok(NULL," ");
  //char* version =  strtok(NULL," ");

  char * method= text;
  char* cur = strpbrk(text," \t");
  // 拆分 请求行
  if(!cur)
  {
    return BAD_REQUEST; 
  }
  *cur++ = '\0';

  m_url = cur;
  cur = strpbrk(m_url," \t");
  if(!cur)
  {
    return BAD_REQUEST; 
  }
  *cur++ = '\0';

  m_version = cur;
 
  // 处理方法
  if(strcasecmp(method,"GET") == 0)
  {
    m_method = GET;
  }
  else if(strcasecmp(method,"POST") == 0)
  {
    m_method = POST;
  }
  else 
  {
    printf(" Can't handle this method\n");
    return BAD_REQUEST;
  }


  // 处理版本 
  if(( strncasecmp(m_version,"HTTP/1.1",8) != 0  ) && ( strncasecmp(m_version,"HTTP/1.0",8) != 0  ))
  {
    printf("not  supported http versoin\n");
    return BAD_REQUEST;
  }
  //printf("%s\n",method);
  //printf("%s\n",url);
  //printf("%s\n",version);
  
  m_parse_status = PARSE_HEADER;
  return LOCAL_REQUEST;
}
HttpConnec::HTTP_CODE HttpConnec::parse_header(char* text)
{
  //空行
  if(text[0] == '\0') 
  {
    //看是否要读取正文
    if(m_content_length != 0)
    {
      printf("m_content_length != 0\n");
      m_parse_status = PARSE_CONTENT;
      return LOCAL_REQUEST;
    }
    //POST但是没有正文,出错
   else if(m_content_length == 0 && m_method == POST)
    {
      return BAD_REQUEST;
    }
    else  
    return OK_REQUEST;
  }

  // 目前只关心长连接和content length
  else if(strncasecmp(text,"Content-Length: ",16) == 0)
  {
    
    text += 16;
    m_content_length = atoi(text);
    m_parse_status = PARSE_HEADER;
  }
  else if(strncasecmp(text,"Connection: ",strlen("Connection: ")) == 0)
  {
    text += 12;
    if(strcasecmp(text,"keep-alive") == 0)
      m_linger = true;
  }
  // 剩下字段TODO
  
  return LOCAL_REQUEST;
}
HttpConnec::HTTP_CODE HttpConnec::parse_content(char* text)
{
  //CGI TODO
  printf("im in parse_content\n");
  m_content = text;
  printf("i got content%s\n",text);
  return OK_REQUEST;
}
HttpConnec::HTTP_CODE HttpConnec::request_check()
{
  m_request_syntax_check = parse_request();
  if(m_request_syntax_check != OK_REQUEST)
  {
    return BAD_REQUEST;
  }
  else 
  {
    return do_request();
  }
}
//TODO
bool HttpConnec::check_url_parameter(char* mrl)
{
  //在处理request line 使用strpbrk比较字符串
  char* cur = strchr(mrl,'?');
  if(cur == NULL)
    return false;
  *cur++ = '\0';
  m_cgi_parameter = cur;
  //printf("m_cgi_parameter:%s\n",m_cgi_parameter);
  return true;
}
HttpConnec::HTTP_CODE HttpConnec::do_request()
{
    //printf("requset_syntax right\n");
    //return OK_REQUEST;
    if(m_method == GET || m_method == POST)
    {
      if(m_method == POST)
        m_needCGI = true;
      else if(m_method == GET)
      {
        m_needCGI = check_url_parameter(m_url); 
      }
   }
    //printf("request_url:%s\n",m_url);
    memset(m_request_file,0,sizeof(m_request_file));

    sprintf(m_request_file,"%s%s",DocRoot,m_url);
    if(strcmp(m_request_file,"./www/") == 0)
    {
      strcat(m_request_file,"index.html");
    }
    //printf("m_request_file:%s\n",m_request_file);
    //走在这里 已经将url拼接好
    if(m_needCGI)
    {
      //CGI函数  
      bool ret = CGIentry(); 
      if(!ret)
      {
        return BAD_REQUEST;
      }
      return OK_REQUEST;
    }
    else 
    {
    if(stat(m_request_file,&m_file_stat) < 0)
    {
      return NOT_FOUND;
    }
    if((!(m_file_stat.st_mode & S_IROTH)))
    {
      return FORBIDDEN_REQUEST; 
    }
    if(m_file_stat.st_mode & S_IFDIR)
    {
      return FORBIDDEN_REQUEST; 
    }
    int fd = open(m_request_file,O_RDONLY); 
    m_file_address = (char*)mmap(0, m_file_stat.st_size,PROT_READ,MAP_PRIVATE,fd,0);
  close(fd);
    }
    //printf("%s",m_file_address);
  return  OK_REQUEST;
}
bool HttpConnec::PHPentry()
{
    char* argv[] ={"php",m_request_file,NULL};
    execvp("php",argv);
    return false;
}
bool HttpConnec::CGIentry()
{
  if(m_cgi_parameter == NULL)
    return false;
  if(m_method != POST && m_method != GET)
  {
    return false;
  }
  // 需要运行的的CGI在 url中
  setenv("QUERY_STRING",m_cgi_parameter,0);
  setenv("METHOD",m_method == POST? "POST":"GET",0);
  
  
  int sockfd[2];
  
  int ret = socketpair(AF_LOCAL,SOCK_STREAM,0,sockfd);
  assert(ret >= 0);
  int pid = fork();
  assert(pid >= 0);
  
  if(pid == 0)
  {
    close(m_epollfd);
    close(m_sockfd);
    close(sockfd[0]);
    dup2(sockfd[1],fileno(stdout));
    //支持脚本函数
    //查看m_requset_file 的后缀 区分不同脚本
    return PHPentry();    
    char* argv[] = {m_request_file,NULL};
    execvp(m_request_file,argv);
  }
  else if(pid >0)
  {
    close(sockfd[1]);
    if(m_method == POST)
    {
      printf("In POST\n");
      send(sockfd[0],m_content,m_content_length,0);
    }
    int ret = recv(sockfd[0],m_cgi_address,sizeof(m_cgi_address),0);
    if(ret < 0)
    {
      printf("CGI recvError\n");
      return false;
    }
    if(ret == 0)
    {
      printf("CGI close\n");
      return false;
    }
    m_cgi_address[ret] = 0;
    //printf("已经读取字符:%d\n",ret);
    //printf("m_cgi_address:%s\n",m_cgi_address);
    return true;
  }
  return true;
}

void HttpConnec::unmap()
{
  if(m_file_address)
  {
    munmap(m_file_address,m_file_stat.st_size);
    m_file_address = NULL;
  }
}
// 都往wirtebuf中写入
bool HttpConnec::add_response(const char* format,...)
{
    if( m_write_idx >= WRITE_BUFFER_SIZE )
    {
        return false;
    }
    //printf("im here\n");
    va_list arg_list;
    va_start( arg_list, format );
    int len = vsnprintf( m_write_buf + m_write_idx,
    WRITE_BUFFER_SIZE - 1 - m_write_idx,
    format, arg_list );
    if( len >= ( WRITE_BUFFER_SIZE - 1 - m_write_idx ) )
    {
        return false;
    }
    m_write_idx += len;
    va_end( arg_list );
    //printf("%s\n",m_write_buf);
    return true;
}
bool HttpConnec::add_status_line( HTTP_CODE status)
{
  char * title;
  switch(status)
  {
    case 200:
     title = "OK" ;
     break;
    case 400:
     title = "Bad Request";
    case 403:
     title = "Forbidden";
    case 404:
     title = "Not Found";
  }
    return add_response( "%s %d %s\r\n", "HTTP/1.1", status, title );
}
// 文件的content_len
void HttpConnec::add_headers(int content_len)
{
 add_content_length(content_len) ;
 add_linger(); 
 add_blank_line();
 //这里之前是返回值bool 但没有返回值 会出现 非法指令错误
}
bool HttpConnec::add_content_length(int content_len)
{
  return add_response("Content-Length: %d\r\n",content_len);
}
bool HttpConnec::add_linger()
{
  return add_response("Connection: %s\r\n",(m_linger == true)? "keep-alive" : "close");
}

bool HttpConnec::add_blank_line()
{
  return add_response("%s","\r\n");
}

bool HttpConnec::add_content( const char* content )
{
    return add_response("%s", content);
}

bool HttpConnec::write()
{
  // TODO
    //int cur_index = 0;
    int temp = 0;
    int bytes_have_send = 0;
    int bytes_to_send = m_write_idx;
    if ( bytes_to_send == 0 )
    {
        modfd( m_epollfd, m_sockfd, EPOLLIN );
        init();
        printf("bytes_to_send == 0 over\n");
        return true;
    }
    //写的时候肯定是就绪事件
    while( 1 )
    {
          temp = writev( m_sockfd, m_iv, m_iv_count );
          printf (" send %d bytes data to client \n",temp);
          if ( temp <= -1 )
          {
              if( errno == EAGAIN )
              {
                //再次尝试读取
                  modfd( m_epollfd, m_sockfd, EPOLLOUT );
                  printf("EAGAIN,send over\n");
                  return true;
              }
              unmap();
              return false;
          }

          bytes_to_send -= temp;
          bytes_have_send += temp;
            //这里假设 temp返回的就是 一次完整的写入
          if ( bytes_to_send <= bytes_have_send )
          {
              unmap();
              if( m_linger )
              {
                  printf("keep-alive,send over\n");
                  init();
                  modfd( m_epollfd, m_sockfd, EPOLLIN );
                  return true;
              }
              else
              {
                  printf("not keep-alive,send over\n");
                  modfd( m_epollfd, m_sockfd, EPOLLIN );
                  return false;
            } 
        }
    }
}
bool HttpConnec::write_respone(HTTP_CODE ret)
{
  switch(ret)
  {
    case BAD_REQUEST:
        {
          add_status_line(BAD_REQUEST);
          //TODO
          //打开语法错误
          add_headers(strlen(error_400_form));
          if(!add_content(error_400_form))
          {
            return false;
          }
        }
    break;
        case NOT_FOUND:
        {
         printf("=========================\n");
         printf("以下是服务响应信息\n");
         printf("%s",m_write_buf);
         printf("%s",m_file_address);
         printf("=========================\n");
          add_status_line(NOT_FOUND);
          add_headers(strlen(error_404_form));
          if ( ! add_content( error_404_form ) )
          {
            return false;
          }
        }
      break;
   case FORBIDDEN_REQUEST:
       {
           add_status_line(FORBIDDEN_REQUEST);
           add_headers( strlen( error_403_form ) );
           if ( ! add_content( error_403_form ) )
           {
               return false;
           }
       }
       break;
   case OK_REQUEST:
       {

         add_status_line(OK_REQUEST);
         if(m_needCGI)
         {
           add_headers(strlen(m_cgi_address));
         }
         else 
         {
           add_headers(m_file_stat.st_size);
         }
         printf("=========================\n");
         printf("以下是服务响应信息,注意打印格式是c风格字符串,所以可能会有乱码\n");
         printf("%s",m_write_buf);

         m_iv[0] .iov_base = m_write_buf;
         m_iv[0] .iov_len= m_write_idx;
         if(m_needCGI)
         {
           m_iv[1] .iov_base = m_cgi_address;
           printf("father get respone: %s\n",m_cgi_address);
           m_iv[1] .iov_len= strlen(m_cgi_address);
           printf("=========================\n");
         }
         else 
         {
           m_iv[1] .iov_base = m_file_address;
           m_iv[1] .iov_len = m_file_stat.st_size;
           printf("%s",m_file_address);
           printf("=========================\n");
         }
         m_iv_count = 2;
         return true;
       }
       break;
   default:
       {
         return false;
       }
  }

    m_iv[0].iov_base = m_write_buf;
    m_iv[0].iov_len = m_write_idx;
    m_iv_count = 1;
    return true;
}
void HttpConnec::process()
{
    write_respone(request_check()); 
    if(!write())
    {
      close_connec();
    }
}
