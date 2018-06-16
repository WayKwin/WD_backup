#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#include<strings.h>
#include <string.h>
#include<ctype.h>

#include<sys/sendfile.h>
#include <sys/stat.h>
#include<fcntl.h>

#define BUFF_SIZE 1024 
#define PORT 8080

int startup();
int  ClearRequest(int sock);
int Deal_Header( char* buf,int sock);
int  get_line(int sock,char buf[],int length);
int deal_msg(int sock);
int     deal_sock(int sock, struct sockaddr_in* clinet_addr,int listen_sock);
// 处理
int HandleMethod(char* );

int EchoErrorCode(int ErrorCode,int sock);

