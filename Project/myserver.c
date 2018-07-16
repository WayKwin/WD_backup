#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "poolsocket.h"

//回调函数掌握的知识体系
//1 从调用的角度理解 ：谁使用函数指针做函数参数的api函数 ，谁去提供函数的入口地址
//2 从回调的角度去理解：
//3 从回调的意义：


void *mystart_routine(void *arg)
{
	
	int 			ret = 0;
	int 			mytime = 3;
	int  connfd = (int)arg;
	printf("func mystart_routine() begin\n");
	
	unsigned char 		*out = NULL;
	int 				outlen = 0; 
	
	while (1)
	{
		//服务器端端接受报文
		ret =  sckServer_rev(connfd, mytime, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
		{
			printf("func sckServer_rev() err: 监测到客户端已经关闭:%d\n", ret);
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			continue;
			
		}
		else if (ret == 0)
		{
			;
		}
		else
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_rev() err:%d\n", ret);
			break;
		}
		
		printf("out:%s \n", out);
		
		//服务器端发送报文
		ret = sckServer_send(connfd, mytime, out, outlen);
		if (ret == Sck_ErrPeerClosed)
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_send() err: 监测到客户端已经关闭:%d\n", ret);
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			sck_FreeMem((void **)&out);
			continue;
			
		}
		else if (ret == 0)
		{
			;
		}
		else
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_send() err:%d\n", ret);
			break;
		}
		
		sck_FreeMem((void **)&out);

	}

	sckServer_close(connfd);
		
	
	printf("func mystart_routine() end\n");
	return NULL;
}

int main()
{
	int					ret = 0;
	int 				port = 8001;
	int 				listenfd = 0, mytime = 3;
	int 				connfd = 0;
	pthread_t 			pid;
	

	printf("hello...\n");
	
	//函数声明
	//服务器端初始化
	ret =  sckServer_init(port, &listenfd);
	if (ret != 0)
	{
		printf("fucn sckServer_init() err:%d \n");
		return ret;
	}
	
	while (1)
	{
		// 0 
		ret = sckServer_accept(listenfd, mytime, &connfd);
		if (ret == Sck_ErrTimeOut)
		{
			printf("fucn sckServer_accept() warning:%d \n");
			continue;
		}
		else if (ret == 0)
		{
			;
		}
		else
		{
			printf("func sckServer_accept) err: %d \n", ret);
			break;
		}
		
	

       	pthread_create(&pid, NULL, mystart_routine, (void *)connfd);
                        
		
	}
	

	//服务器端环境释放 
	sckServer_destroy();


	return 0;	
}
