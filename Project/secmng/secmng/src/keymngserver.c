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
#include "keymngserverop.h"
#include "keymnglog.h"

//所有的配置信息  做成全局变量
MngServer_Info 			mngServerInfo;

void *mystart_routine(void *arg)
{
	int 			ret = 0;
	int 			mytime = 3;
	
	//客户端请求报文
	MsgKey_Req			*pMsgKeyReq = NULL;
	int 				iMsgKeyType = 0;
	
	//服务器应答报文 数据
	unsigned char 		*pMsgKeyResData = NULL;
	int 				iMsgKeyResDataLen = 0;
	
	int  connfd = (int)arg;
	printf("func mystart_routine() begin\n");
	
	unsigned char 		*out = NULL;
	int 				outlen = 0; 
	
	while (1)
	{
		//服务器端端接受报文
		ret =  sckServer_rev(connfd, mytime, &out, &outlen); //1
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"1111111111111111111111111111111111111");
		if (ret == Sck_ErrPeerClosed)
		{
			printf("func sckServer_rev() err: 监测到客户端已经关闭:%d\n", ret);
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			continue;
		}
		else if (ret != 0)
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_rev() err:%d\n", ret);
			break;
		}
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"222222222222222222");
		
		//解析客户端的请求数据 请求结构体
		ret = MsgDecode(out, outlen, (void **)&pMsgKeyReq, &iMsgKeyType);
		if (ret != 0)
		{
			sck_FreeMem((void **)&out);
			printf("func MsgDecode() err:%d\n", ret);
			continue; //
		}
		sck_FreeMem((void **)&out); //收到的客户端请求数据包 没有了
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"33333333333333333");
		
		switch (pMsgKeyReq->cmdType)
		{
		case KeyMng_NEWorUPDATE:
			//密钥协商应答 //封装一个api函数 作用:产生一个应答报文
			ret = MngServer_Agree(&mngServerInfo,  pMsgKeyReq,   &pMsgKeyResData, &iMsgKeyResDataLen);
			if (ret != 0)
			{
				KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"33333333333333---1");
				printf("func KeyMngServer_Agree() err:%d\n", ret);
				break;;
			}
			KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"444444444444444444444444");
			break;	
		case KeyMng_Check:
			//密钥协商应答
			break;	
		case KeyMng_Revoke:
			//密钥协商应答
			break;
		default:
			ret = MngSvr_ParamErr;
			printf("客户端的请求cmdtype err:%d\n", pMsgKeyReq->cmdType);
			break; 
		}
		
		//做业务失败
		if (ret != 0)
		{
			//MsgKey_Res msgkeyRes; MsgEncode()
			printf("处理业务流失败ret:%d \n", ret);
			//错误处理流程 ....
			goto End;
		}
		
		//服务器端发送报文
		
		ret = sckServer_send(connfd, mytime, pMsgKeyResData, iMsgKeyResDataLen);
		if (ret == Sck_ErrPeerClosed)
		{
			KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"55555555555555555555555");
			printf("func sckServer_send() err: 监测到客户端已经关闭:%d\n", ret);
			goto End;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			goto End;
			
		}
		else if (ret != 0)
		{
			printf("func sckServer_send() err:%d\n", ret);
			goto End;
		}
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[3], ret,"6666666666666666666666");
	End:
		if (pMsgKeyReq != NULL) MsgMemFree( (void ** )&pMsgKeyReq, iMsgKeyType); //
		if (pMsgKeyResData != NULL)  MsgMemFree( (void ** )&pMsgKeyResData, 0); //
		
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

	memset(&mngServerInfo, 0, sizeof(MngServer_Info));

	//keymngsever初始化 
	//设计与实现  初始化什么元素 定义一个结构 
	//1 数据库的连接信息从配置文件中获取 secmng secmng orcl 
	//2 自身服务器网点信息 serverid 名称  服务器端支持的最大网点个数
	ret =  MngServer_InitInfo(&mngServerInfo);
	if (ret != 0)
	{
		printf("keymngserver 初始化失败 err:%d \n", ret);
		return ret;
	}
	
	//函数声明
	//服务器端初始化
	ret =  sckServer_init(port, &listenfd);
	if (ret != 0)
	{
		printf("fucn sckServer_init() err:%d \n", ret);
		return ret;
	}
	
	while (1)
	{
		// 0 
		ret = sckServer_accept(listenfd, mytime, &connfd);
		if (ret == Sck_ErrTimeOut)
		{
			printf("fucn sckServer_accept() warning:%d \n", ret);
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

