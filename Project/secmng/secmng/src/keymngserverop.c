#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <pthread.h>

#include "keymnglog.h"
#include "keymngserverop.h"
#include "poolsocket.h"
#include "keymng_msg.h"
#include "myipc_shm.h"
//#include "keymng_shmop.h"
//#include "icdbapi.h"
//#include "keymng_dbop.h"

//初始化服务器 全局变量
int MngServer_InitInfo(MngServer_Info *svrInfo)
{
	int 			ret = 0;
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[1], ret,"func MngServer_InitInfo() begin");
	strcpy(svrInfo->serverId, "0001");
	
	strcpy(svrInfo->dbuse, "SECMNG");  //从配置文件中获取
	strcpy(svrInfo->dbpasswd, "SECMNG");
	strcpy(svrInfo->dbsid, "orcl");
	svrInfo->dbpoolnum = 10;
	
	strcpy(svrInfo->serverip, "127.0.0.1");
	svrInfo->serverport = 8001;
	
	//
	svrInfo->maxnode = 30;
	svrInfo->shmkey = 0x0001;
	svrInfo->shmhdl = 0;
	
	
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[1], ret,"func MngServer_InitInfo() end");	
	return 0;
}



//服务端 密钥协商应答流程
//密钥协商应答流程
/*
1 组织应答报文 
2 编码应答报文msgreal 
3 协商密钥 
4 写共享内存
5 客户端要求: 保存数据库
6 回复应答报文 sockieapi
*/
static int g_keyid = 100;
int MngServer_Agree(MngServer_Info *svrInfo, MsgKey_Req *msgkeyReq, unsigned char **outData, int *datalen)
{
	int 			ret = 0, i = 0;
	
	MsgKey_Res			msgKeyRes; 
	memset(&msgKeyRes, 0, sizeof(MsgKey_Res));
	
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[1], ret,"func MngServer_Agree() begin");
	
	//1 组织应答报文
	msgKeyRes.rv = 0;
	strcpy(msgKeyRes.clientId, msgkeyReq->clientId);
	strcpy(msgKeyRes.serverId, svrInfo->serverId);
	
	for (i=0; i<64; i++)
	{
		msgKeyRes.r2[i] = 'a' + i;
	}
	g_keyid ++;
	msgKeyRes.seckeyid = g_keyid;
 	
 	//2 编码应答报文
 	ret = MsgEncode(&msgKeyRes, ID_MsgKey_Res, outData, datalen);
 	if (ret != 0)
 	{
 		KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], ret,"func MsgEncode() end");	
 		goto End;
 	}
 	
 End:
 	
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[1], ret,"func MngServer_Agree() end");	
	return ret;
}
