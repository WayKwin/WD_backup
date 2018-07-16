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
//
//
// 10个线程 从连接池里拿到已经三次握手的TCP连接
// 进行收发数据
//

 void *mystart_routine (void *arg)
 {
   printf("tid:%lu\n",pthread_self());
 	int			i = 0, ret = 0;
 	void 		*handle  = NULL;
 	int 		connfd = 0;
 	char		*data = (char *)"hello world";
 	int 		datalen = 11;
 	
 	unsigned char 	*out = NULL;
 	int 			outlen = 0;
 	
 	handle = arg;
 	
 		//客户端 socket池 获取一条连接 
	ret = sckCltPool_getConnet(handle, &connfd);
	if (ret != 0)
	{
		printf("func sckCltPool_getConnet() err:%d \n", ret);
		return NULL;
	}
 	
 	for (i=0; i<10; i++)
 	{
		//客户端 socket池 发送数据 
		ret = sckCltPool_send(handle, connfd, 
        (unsigned char*)data, datalen);
		if (ret != 0)
		{
			printf("func sckCltPool_send() err:%d \n", ret);
			break;
		}
		
		
		//客户端 socket池 接受数据
		ret = sckCltPool_rev(handle,  connfd, &out, &outlen); //1
		if (ret != 0)
		{
			printf("func sckCltPool_rev() err:%d \n", ret);
			break;
		}
		printf("out:%s \n", out);
		sck_FreeMem(( void **) &out);
 	}
 	
 	//客户端 socket池 把连接放回 socket池中 
  // ret != 0 是break退出循环的
 	if (ret != 0)
 	{
 		ret = sckCltPool_putConnet(handle, connfd, 1); //0正常 1 //断链修复
 	}
 	else
 	{
 		ret = sckCltPool_putConnet(handle, connfd, 0); //0正常 1
 	}
	
 	return NULL;
 }



int main()
{
	int 		ret = 0, i = 0;
	printf("client3 ....\n");
	
	SCKClitPoolParam			scPoolParam;
	void 		*handle  = NULL;
	pthread_t 	pid[1024];
	
	memset(&scPoolParam, 0, sizeof(SCKClitPoolParam));
	strcpy(scPoolParam.serverip, "127.0.0.1");
	scPoolParam.serverport = 8080;
	scPoolParam.bounds = 10;
	scPoolParam.connecttime = 3;
	scPoolParam.sendtime = 3;
	scPoolParam.revtime = 3;
	
	
	//客户端 socket池初始化
	ret = sckCltPool_init(&handle, &scPoolParam);
	if (ret != 0)
	{
		printf("func sckCltPool_init() err:%d \n", ret);
		return ret;
	}
	
	printf("任意键继续。。。。\n");
	getchar();
	
	for (i=0; i<10; i++)
	{
	   pthread_create(&pid[i], NULL, mystart_routine, (void *)handle);
	}
// 等待线程	
	for (i=0; i<10; i++)
	{
		pthread_join(pid[i], NULL);
	}
	 	
	
	//客户端 socket池 销毁连接
	ret = sckCltPool_destroy(handle);


	return ret;	
}



