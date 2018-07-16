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
typedef struct _Thread_Info{
  int ArrayIndex;
  int Loop;
  void *handle;
}thread_info;
 void *my_start_routine (void *arg)
 {
 	int					i = 0, ret = 0;
 	void 				*handle  = NULL;
 	int 				connfd = 0;
 	char				data[256] = {0};
 	int 				datalen = 11;
 	thread_info *pThreadInfo;
 	
 	unsigned char 		*out = NULL;
 	int 				outlen = 0;
 	
 	pThreadInfo = (thread_info*)arg;
 	handle = pThreadInfo->handle;
 	
 		//客户端 socket池 获取一条连接 
	ret = sckCltPool_getConnet(handle, &connfd);
	if (ret != 0)
	{
		free(arg);
		printf("func sckCltPool_getConnet() err:%d \n", ret);
		return NULL;
	}
 	
 	for (i=0; i<pThreadInfo->Loop; i++)
 	{
		//客户端 socket池 发送数据 
		memset(data, 0, sizeof(data));
		sprintf(data, "第%d线程 第%d圈", pThreadInfo->ArrayIndex+1, i+1);
		
		ret = sckCltPool_send(handle, connfd,  (unsigned char*)data, strlen(data));
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
		printf("out: %s \n", out);
		sck_FreeMem(( void **) &out);
 	}
 	
 	//客户端 socket池 把连接放回 socket池中 
 	if (ret != 0)
 	{
 		ret = sckCltPool_putConnet(handle, connfd, 1); //0正常 1 //断链修复
 		
 	}
 	else
 	{
 		ret = sckCltPool_putConnet(handle, connfd, 0); //0正常 1
 	}
	
  free(arg);
 		 
 	return NULL;
 }

int main()
{
  int ret = 0, i = 0; 
  SCKClitPoolParam sockPool;
  void *handle = NULL;
  pthread_t pid[1024];

	memset(&sockPool, 0, sizeof(SCKClitPoolParam));
	strcpy(sockPool.serverip, "127.0.0.1");
  sockPool.serverport = 8080;
  sockPool.bounds = 10;
  sockPool.connecttime = 3;
  sockPool.sendtime = 3;
  sockPool.revtime = 3;

  int ThreadNum= 0,Loop = 0;

  printf("please input ThreadNum\n");
  scanf("%d",&ThreadNum);
  printf("please input Loop\n");
  scanf("%d",&Loop);
  
  sckCltPool_init(&handle,&sockPool);

  if(ret != 0)
  {
    printf("fun  sckCltPool_init() err\n");
    return ret;
  }
  thread_info tis[100];

  memset(tis,0,sizeof(tis));

  thread_info* ti  =NULL;
  for(i = 0; i < ThreadNum;i++)
  {
    ti = (thread_info*)malloc(sizeof(thread_info));
    /*thread_info ti = tis[i];*/
    ti->ArrayIndex = i;
    ti->handle = handle;
    ti->Loop = Loop;
    pthread_create(&pid[i],NULL,my_start_routine,(void*)ti);
  }

	for (i=0; i<ThreadNum; i++)
	{
		pthread_join(pid[i], NULL);
	}
	 	
	//客户端 socket池 销毁连接
	ret = sckCltPool_destroy(handle);

	return ret;	
}
