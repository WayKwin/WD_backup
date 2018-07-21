#include"../incl/keymngclientop.h"
#include "../incl/keymnglog.h"
#include  "../incl/keymng_msg.h"
#include "../incl/poolsocket.h"
#include<stdio.h>
#include<string.h>
#include<unistd.h>



int MngClient_InitInfo(MngClient_Info *pCltInfo)
{
  int ret = 0;
  if(pCltInfo == 0)
  {
    ret = MngClt_ParamErr;
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func main() MngClient_InitInfo() err (pCltInfo == NULL)");
  }
  strcpy(pCltInfo->clientId,"1111");
  strcpy(pCltInfo->serverId,"1111");
  strcpy(pCltInfo->AuthCode,"1111");
  strcpy(pCltInfo->serverip,"127.0.0.1");
  pCltInfo->serverport = 8080;
  pCltInfo->maxnode = 1;
  pCltInfo->shmkey = 0x1111;
  //pCltInfo->shmkey = 0x;
  return ret;
}
int MngClient_Agree(MngClient_Info *pCltInfo)
{
  int ret = 0;
  int i = 0; 

  //编解码
  MsgKey_Req msgReq;
  unsigned char* outData = NULL;
  int outLen= 0;
  MsgKey_Res* msgRes = NULL;
  int type = ID_MsgKey_Res;

  //连接用
  char* server_ip = pCltInfo->serverip;
  printf("server_ip:%s\n",server_ip);
  int server_port = pCltInfo->serverport;
  printf("server_port:%d\n",server_port);
  int connfd = -1;
  int sendtime = 3;
  int connect_time = 3;
  int revtime = 3;

  memset(&msgReq, 0, sizeof(MsgKey_Req));

  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[1],ret,"func MngClient_Agree() begin");
  //更新
  msgReq.cmdType = KeyMng_NEWorUPDATE;
  strcpy(msgReq.clientId,pCltInfo->clientId);
  strcpy(msgReq.serverId,pCltInfo->serverId);
  strcpy(msgReq.AuthCode,pCltInfo->AuthCode);
  //strcpy(msgReq.r1,pCltInfo->);
  for(; i < 65;i++)
  {
    msgReq.r1[i] = 'a'+i;
  }
  ret = MsgEncode((void*)&msgReq,ID_MsgKey_Req,&outData,&outLen);
  printf("client outData:%s\n",outData);
  if(ret != 0)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() MsgEncode()");
  goto END;
  }

  sckClient_init();
  
  ret = sckClient_connect(server_ip,server_port,connect_time,&connfd);
  if(ret != 0)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() connect()");
  goto END;
  }
  
  ret = sckClient_send(connfd,sendtime,outData,outLen);
  if(ret == Sck_ErrTimeOut)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() sckClient_send() Sck_ErrTimeOut");
    goto END;
  }
  if(ret != 0)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() sckClient_send()");
    goto END;
  }

  MsgMemFree((void**)&outData,0);
  outLen = 0;

  ret = sckClient_rev(connfd,revtime,&outData,&outLen);
  if(ret == Sck_ErrTimeOut)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() sc kClient_rev() Sck_ErrTimeOut");
    goto END;
  }
  if(ret != 0)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() sckClient_rev()");
    goto END;
  }

  // 进去msgReq 会将outData第一层解码 判断类型,然后用输出型参数传递给你
  ret = MsgDecode(outData,outLen,(void**)&msgRes,&type);
  if(type != ID_MsgKey_Res)
  {
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() MsgDecode() TypeError");
    //打日志,类型出错 
    goto END;
  }
  // rv是 编解码的返回值
  if(msgRes->rv == 0)
  {
    printf("编解码成功\n");
  }
  else 
  {
    printf("编解码失败\n");
  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func MngClient_Agree() MsgDecode() DecodeError");
  }
  //

END:
  if(outData != NULL)
    MsgMemFree((void**)&msgRes,0);
  if(connfd > 0)
    close(connfd);
  if(msgRes != NULL)
    MsgMemFree((void**)msgRes,ID_MsgKey_Res);
  sckClient_destroy();

  KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[1],ret,"func MngClient_Agree() end ");

  return ret;
}
