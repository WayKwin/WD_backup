

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <pthread.h>


#include "keymng_msg.h"
#include "myipc_shm.h"
#include "poolsocket.h"
#include "keymnglog.h"
#include "keymngclientop.h"
//#include "keymng_shmop.h"  //网点密钥

int MngClient_InitInfo(MngClient_Info *pCltInfo)
{
	int 		ret = 0;
	
	if (pCltInfo == NULL)
	{
		ret = MngClt_ParamErr;
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func main() MngClient_InitInfo() err (pCltInfo == NULL)");
		return ret;
	}

	strcpy(pCltInfo->clientId, "1111");
	strcpy(pCltInfo->AuthCode, "1111");
	strcpy(pCltInfo->serverId, "0001");
	strcpy(pCltInfo->serverip, "127.0.0.1");
	
	pCltInfo->serverport = 8001;
	pCltInfo->maxnode = 1; //
	pCltInfo->shmkey = 0x1111;
	//pCltInfo->shmhdl;
	
	
	return ret;
}



/*
客户端密钥请求和接受

1 组织请求报文
2 msgreallib编码生成二进制流
3 socketapi发送报文
4 socketapi 接受报文
5 msgreallib解析服务器的数据得到结构体
6 协商密钥
7 shmapi写共享内存
*/


int MngClient_Agree(MngClient_Info *pCltInfo)
{
	int ret = 0, i = 0;
	MsgKey_Req			msgKeyReq;
	
	unsigned char		*outData = NULL;
	int					outLen = 0;
	int 				mytime = 3;
	int 				connfd = 0;

	 unsigned char 		*msgKey_ResData = NULL;
	 int				msgKey_ResDataLen = 0;
	 
	 MsgKey_Res			*pMsgKeyRes = NULL;
	 int 				iMsgKeyResType = 0;
	// 没有标记rv 
	memset(&msgKeyReq, 0, sizeof(MsgKey_Req));
	
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[1], ret,"func MngClient_Agree() begin");
	
	//1 组织请求报文
	msgKeyReq.cmdType = KeyMng_NEWorUPDATE;
	strcpy(msgKeyReq.clientId,pCltInfo->clientId );
	strcpy(msgKeyReq.AuthCode,pCltInfo->AuthCode );
	strcpy(msgKeyReq.serverId,pCltInfo->serverId );
	for (i=0; i<64; i++) //模拟
	{
		msgKeyReq.r1[i] = 'a' + i;
	}

	//2 msgreallib编码生成二进制流
	ret = MsgEncode(&msgKeyReq, ID_MsgKey_Req, &outData, &outLen);
	if (ret != 0)
	{
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func MsgEncode() err");
		return ret;
	}
	
	//3 socketapi发送报文
	//客户端 初始化
	ret = sckClient_init();
	if (ret != 0)
	{
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func sckClient_init() err");
		goto End;
	}
	
	//客户端 连接服务器
	ret = sckClient_connect(pCltInfo->serverip, pCltInfo->serverport, mytime, &connfd);
	if (ret != 0)
	{
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func sckClient_connect() err serverip:%s serverport%d :", pCltInfo->serverip, pCltInfo->serverport);
		goto End;
	}
	
	//客户端 发送报文
	ret = sckClient_send(connfd, mytime, outData, outLen);
	if (ret != 0)
	{
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func sckClient_send() err");
		goto End;
	}

	//客户端 接受报文
	ret = sckClient_rev(connfd, mytime, &msgKey_ResData, &msgKey_ResDataLen); //1
	if (ret != 0)
	{
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func sckClient_rev() err");
		goto End;
	}
	
	//4 解码服务器的应答报	 
	ret = MsgDecode( msgKey_ResData, msgKey_ResDataLen, (void **)&pMsgKeyRes, &iMsgKeyResType);
	if (ret != 0)
{
		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func MsgDecode() err");
		goto End;
	}
	
	if (pMsgKeyRes->rv == 0)
	{
		printf("服务器端处理业务seckeyid:%d ok\n", pMsgKeyRes->seckeyid);
	}
	else 
	{
		printf("服务器端处理业务 err\n");
		goto End;
	}
	
	//r1 r2 //协商密钥 写共享内存

End:
	if (outData != NULL)   		MsgMemFree((void **)&outData, 0);	
	//客户端 关闭和服务端的连接
	if (connfd > 0) 	 		sckClient_closeconn(connfd);	
	//客户端 释放内存
	if (msgKey_ResData != NULL) sck_FreeMem((void **)&msgKey_ResData);
	if (pMsgKeyRes != NULL)		MsgMemFree((void **)&pMsgKeyRes, iMsgKeyResType);
	//客户端 释放
	sckClient_destroy();
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[1], ret,"func MngClient_Agree() end");
	return ret;
	
}
