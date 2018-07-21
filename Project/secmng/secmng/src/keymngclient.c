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
#include "keymnglog.h"

#include "poolsocket.h"
#include "keymngclientop.h"
#include "keymng_msg.h"

int Usage()
{
    int nSel = -1;
    
    system("clear");    
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n  /*     1.密钥协商                                            */");
    printf("\n  /*     2.密钥校验                                            */");
    printf("\n  /*     3.密钥注销                                            */");
    printf("\n  /*     4.密钥查看                                            */");
    printf("\n  /*     0.退出系统                                            */");
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n\n  选择:");
    scanf("%d", &nSel);
    while(getchar() != '\n'); //把应用程序io缓冲器的所有的数据 都读走,避免影响下一次 输入
    
    return nSel;
}


int mainxxxxxx()
{
	printf("keymngclient hello...\n");
	keymng_log(__file__, __line__,keymnglevel[0], 0,"func main() 0000000000000000 ");
	keymng_log(__file__, __line__,keymnglevel[1], 1,"func main() 111111111111 ");
	keymng_log(__file__, __line__,keymnglevel[2], 2,"func main() 2222222222222222 ");
	keymng_log(__file__, __line__,keymnglevel[3], 3,"func main() 333333333333");
	keymng_log(__file__, __line__,keymnglevel[4], 4,"func main() 44444444444 ");
	
	return 0;
}


int main()
{
	int 						ret = 0;
	int 						nSel = 0;
	MngClient_Info  			mngClientInfo;
	
	memset(&mngClientInfo, 0, sizeof(MngClient_Info));
	
	
	//设计初始化的元素 目标:出来一个结构体
	//读配置文件  clientid authcode, serverid serverip sreverprot clientshmkey
	
	//初始化客户端 全局变量
	ret = MngClient_InitInfo(&mngClientInfo);
	if (ret != 0)
	{
		printf("func MngClient_InitInfo() err:%d\n", ret);
		return ret;
	}
	
	while (1)
	{
		nSel =  Usage();
		switch (nSel)
		{
		case 0:
			//系统退出
			return 0 ;
		case 1:
			// 密钥协商
			ret = MngClient_Agree(&mngClientInfo);
			break ;
		case 2:
			//密钥校验
			break ;
		case 3:
			//密钥注销
			break ;
		}
		
		if (ret)
		{
			printf("\n!!!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!");
			printf("\n错误码是：%x\n", ret);
		}
		else
		{
			printf("\n!!!!!!!!!!!!!!!!!!!!SUCCESS!!!!!!!!!!!!!!!!!!!!\n");
		}	
		getchar();	
	}
	
	return 0;
}



