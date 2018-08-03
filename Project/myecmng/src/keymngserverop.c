#include <string.h>

#include <time.h>
#include <pthread.h>
#include<signal.h>

#include "../incl/keymnglog.h"
#include "../incl/keymngserverop.h"
#include "../incl/poolsocket.h"
#include "../incl/keymng_msg.h"
#include "../incl/keymng_shmop.h"

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
int g_keyid = 0;
int MngServer_InitInfo(MngServer_Info *svrInfo)
{
  int ret;
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

  ret = KeyMng_ShmInit(svrInfo->shmkey,svrInfo->maxnode,&svrInfo->shmhdl);
  if(ret != 0)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"KeyMng_ShmInit() Error");
    return ret;
  }

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
 // 构建应答报文
  msgRes.rv = 0;
  strcpy(msgRes.serverId,msgKeyReq->serverId);
  strcpy(msgRes.serverId,msgKeyReq->serverId);
  for(i = 0; i < 64; i++)
  {
    msgRes.r2[i] = 'a' + i;
  }
  // 每次应答,都自增id
  g_keyid++;
  msgRes.seckeyid = g_keyid;
    // 编码应答报文
  ret = MsgEncode((void*)&msgRes,ID_MsgKey_Res,pMsgKeyResData,iMgKeyResDataLen);

  if(ret < 0)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[3],0,"MsgEncode() Error");
    goto END;
  }
  //3 协商密钥 
  // 上面给客户端应答了之后,还要用共享内存, 写入网点信息(在数据库中)  
  NodeSHMInfo nodeShmInfo;
  memset(&nodeShmInfo,0,sizeof(NodeSHMInfo));
  nodeShmInfo.status = 0;
  // 一个网点信息包含 客户端和服务器端ID 
  strcpy(nodeShmInfo.clientId,msgKeyReq->clientId);
  strcpy(nodeShmInfo.serverId,mngServerInfo->serverId);
  nodeShmInfo.seckeyid = g_keyid;//本来是数据库自增字段
  for(i = 0; i < 64; i++)
  {
    // 这个网点的加密规则是 A 和 B 密码的叠加
    nodeShmInfo.seckey[2*i] = msgKeyReq->r1[i];
    nodeShmInfo.seckey[2*i+1] = msgRes.r2[i];
  }
  //写入共享内存
  ret = KeyMng_ShmWrite(mngServerInfo->shmhdl,mngServerInfo->maxnode,&nodeShmInfo);
  if(ret != 0)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"KeyMng_ShmWrite() Error");
    goto END;
  }
END:
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[3],0,"MngServer_Agree() END");
  return ret;
}
/*int MngServer_Check(MngServer_Info *svrInfo, MsgKey_Req *msgkeyReq, unsigned char **outData, int *datalen)*/
/*{*/
/*}*/
/*int MngServer_Revoke(MngServer_Info *svrInfo, MsgKey_Req *msgkeyReq, unsigned char **outData, int *datalen)*/
/*{*/
/*}*/
