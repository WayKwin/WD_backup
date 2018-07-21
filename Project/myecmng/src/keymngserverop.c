#include <string.h>

#include <time.h>
#include <pthread.h>
#include<signal.h>

#include "../incl/keymnglog.h"
#include "../incl/keymngserverop.h"
#include "../incl/poolsocket.h"
#include "../incl/keymng_msg.h"
//TODO
//#include "../incl/myipc_shm.h"
//#include "keymng_shmop.h"
//#include "icdbapi.h"
//#include "keymng_dbop.h"
//server初始化
//设计与实现 
//1 数据库信息,从配置文件中获取, secmng secmn orc1
//2 自身服务器网点信息,serverid 服务器端支持的最大网点
//3  
//初始化服务器 全局变量
int MngServer_InitInfo(MngServer_Info *svrInfo)
{
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[1],0,"%s begin",__FUNCTION__);
  //TODO 配置文件
  strcpy(svrInfo->serverId,"123");
  strcpy(svrInfo->dbuse,"root");
  strcpy(svrInfo->dbpasswd,"1234556");
  strcpy(svrInfo->dbsid,"cwasx");

  strcpy(svrInfo->serverip,"127.0.0.1");
  svrInfo->serverport = 8080;

  svrInfo->maxnode = 30;
  svrInfo->shmkey= 0x001;
  svrInfo->shmhdl = 0;


  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[1],0,"%s end",__FUNCTION__);
  return 0;
}
int  MngServer_Agree(MngServer_Info* mngServerInfo,
                     MsgKey_Req* msgKeyReq,unsigned char**pMsgKeyResData,
                     int *iMgKeyResDataLen)
{

  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[3],0,"MngServer_Agree()");
  int ret = 0;
  int i = 0;
  MsgKey_Res msgRes;

  memset(&msgRes,0,sizeof(MsgKey_Res));

  msgRes.rv = 0;
  strcpy(msgRes.serverId,msgKeyReq->serverId);
  strcpy(msgRes.serverId,msgKeyReq->serverId);
  for(i = 0; i < 64; i++)
  {
    msgRes.r2[i] = 'a' + i;
  }

  msgRes.seckeyid= 0;

  ret = MsgEncode((void*)&msgRes,ID_MsgKey_Res,pMsgKeyResData,iMgKeyResDataLen);

  if(ret < 0)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[3],0,"MsgEncode() Error");
  }
  
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[3],0,"MngServer_Agree() END");
  return 0;
}
#if 0
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
#endif
