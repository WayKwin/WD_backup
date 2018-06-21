#include"http_conn.h"
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
void HttpConnec::init()
{
  // init read 
  m_handled_idx = 0;
  m_read_indx = 0;
  // stat_line = (在link_ok 后)m_handled_indx
  m_start_line = 0;
  m_epollfd = -1;
  memset(m_read_buf,0,sizeof(m_read_buf));

  m_user_count = 0;
  m_sockfd = -1;

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
        //下次接着读
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

  while(( line_status = parse_line())== LINE_OK)
  {
    text = getline();
    m_start_line = m_handled_idx;

    switch(m_parse_status)
    {
      case LOCAL_REQUEST:  
        ret = parse_request_line(text);
        if(ret == BAD_REQUEST)
          return BAD_REQUEST;
          break;
      case 

    }
    
    
    //if(text[0] == '\0')
    //{
      //printf("http request:空行\n");
    //}
    //else printf("http request:%s\n",text);
  }
  printf(" accpet over\n");
  //TODO
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
  if(strcasecmp(m_version,"HTTP/1.1") != 0 || strcasecmp(m_version,"HTTP/1.0") != 0 )
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
      m_parse_status = PARSE_CONTENT;
      return LOCAL_REQUEST;
    }
    //POST但是没有正文,出错
    if(m_content_length == 0 && m_method == POST)
    {
      return BAD_REQUEST;
    }
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
  printf("i got content%s\n",text);
  return OK_REQUEST;
}

