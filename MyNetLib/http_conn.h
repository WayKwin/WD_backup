#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include"locker.h"

class HttpConnec 
{
  public: 
    HttpConnec()=default;
    ~HttpConnec()=default;
    void close_connec(bool readl_close = true);
    void init();
  // HTTP的状态
  private:
    //读取一行的状态
  enum READ_LINE_STATUS {LINE_OK = 0,LINE_BAD,LINE_LOCAL};
    //暂时处理这三个方法
  enum REQUSET_TYPE{GET=0, POST,HEAD};
    //通过协议分析是否是有正文
  enum PARSE_STATUS{PARSE_LINE,PARSE_HEADER,PARSE_CONTENT};
  enum RESPOEND_TYPE{OK=0};
    //HTTP的状态码
  enum HTTP_CODE{LOCAL_REQUEST=0,BAD_REQUEST,OK_REQUEST};
    //CGI处理函数 传入 REQUESET_TYPE cgi另外写一个类
    //TODO

  //用到的静态常量 
  private:
  static const int MAX_FILE_NAME_LEN = 256; 
  static const int READ_BUFFER_SIZE = 2048; 
  static const int WRITE_BUFFER_SIZE= 2048; 
  
  //epoll
  public:
  int m_epollfd;
  int m_user_count;
  int m_sockfd;

  


  //读取相关函数变量
  public:
  bool read();
  READ_LINE_STATUS parse_line();
  char* getline(){return m_read_buf + m_start_line;}
  int m_handled_idx;
  int m_read_indx;
  int m_start_line;
  char m_read_buf[READ_BUFFER_SIZE];

  //分析状态机的转换状态
  PARSE_STATUS m_parse_status;

  //头部分析函数
  HTTP_CODE parse_request();
  HTTP_CODE parse_request_line(char* text);
  //已经处理POST 但是没有正文的情况
  HTTP_CODE parse_header(char* text);
  HTTP_CODE parse_content(char* text);

  bool m_needCGI;

  //关心的请求行字段
  //TODO CGI
  char* m_url;
  REQUSET_TYPE m_method;
  char* m_version; 

  //关心的请求头部字段
  int  m_content_length;
  bool m_linger;
  //TODO
  char* m_host;

  // 客户机请求状态
  HTTP_CODE  m_request_syntax_check;
  HTTP_CODE request_check();
  //处理请求函数
  HTTP_CODE do_request(); 

  //写 TODO
  public:



  


  
  
};
#endif
