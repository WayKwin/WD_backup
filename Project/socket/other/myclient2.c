#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "poolsocket.h"

int main()
{
	int 		ret = 0;
	char 		*ip = "127.0.0.1";
	int 		port = 8001;
	int 		mytime = 3;
	int 		connfd = 0;
	
	char 		*mydata = "abcdefghijklmnopq";
	int 		mydatalen = 8;
	
	 unsigned char 	*myout = NULL;
	 int 			myoutlen = 0;
	
	//客户端 初始化
	ret =  sckClient_init();
	if (ret != 0)
	{
		printf("func sckClient_init() err :%d \n", ret);
		return ret;	
	}
	
	//客户端 连接服务器
	ret = sckClient_connect(ip, port, mytime, &connfd);
	if (ret != 0)
	{
		printf("func sckClient_connect() err :%d \n", ret);
		return ret;	
	}
	
	//客户端 发送报文
	ret = sckClient_send(connfd, mytime, mydata, mydatalen);
	if (ret != 0)
	{
		printf("func sckClient_connect() err :%d \n", ret);
		goto End;
	}
	
	//客户端 接受报文
	ret = sckClient_rev(connfd, mytime, &myout, &myoutlen); //1
	if (ret != 0)
	{
		printf("func sckClient_rev() err :%d \n", ret);
		goto End;
	}

	printf("myout:%s \n", myout);

End:
		
	//客户端 释放内存
	if (myout) 		sck_FreeMem((void **)&myout);
	
	//客户端 关闭和服务端的连接
	if (connfd > 0) 	sckClient_closeconn(connfd);
	
	//客户端 释放
	sckClient_destroy();


	return ret;	
}
