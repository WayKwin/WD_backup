#include<string.h>
#include "../incl/myipc_shm.h"
#include"../incl/keymng_shmop.h"
#include"../incl/keymnglog.h"
#include"../incl/keymngclientop.h"

int  KeyMng_ShmInit(int key,int maxnodenum,int * shmhdl)
{
  int ret = 0;
  void *mapddr = NULL;
  ret = IPC_OpenShm(key,sizeof(NodeSHMInfo)*maxnodenum,shmhdl);
  // 不存在共享内存
  if(ret == MYIPC_NotEXISTErr)
  {
    printf(" 没有共享内存,开始创建...\n");
    // 创建新的共享内存
    ret = IPC_CreatShm(key,sizeof(NodeSHMInfo)*maxnodenum,shmhdl);
    if(ret != 0)
    {
        printf("func IPC_CeatShm() err: %d line: %d\n",ret,__LINE__);
        return ret;
    }
    else 
    {
      //映射内存
        printf("系统创建共享内存 ok, 开始清空共享内存\n");
        ret = IPC_MapShm(*shmhdl,&mapddr);
        if(ret != 0)
        {
        printf("func IPC_MapShm() err: %d line: %d\n",ret,__LINE__);
          // 映射共享内存失败
          return ret;
        }
        memset(mapddr,0,sizeof(NodeSHMInfo)*maxnodenum);

        ret = IPC_UnMapShm(mapddr);
        printf("系统创建共享内存 ok,清空共享内存 ok\n");
    }
  }
  // 有旧的共享内存,使用旧的
  else if (ret == 0)
  {
    printf("系统检测到有共享内存, 使用旧的共享内存 \n"); 
    /*printf("")*/
  }
  else 
  {
    printf("系统监测有旧的共享内存,但打开共享内存失败\n"); 
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func KeyMng_ShmInit() err:");
    // 失败
  }
  return ret; 
}
int KeyMng_ShmWrite(int shmhdl, int maxnodenum, NodeSHMInfo *pNodeInfo)
{
  int ret = 0, i = 0;
  NodeSHMInfo* CurNode =pNodeInfo;
  NodeSHMInfo ZeroNode;
  char* addr = NULL;
  memset(&ZeroNode,0x00,sizeof(ZeroNode));
  if(pNodeInfo == NULL)
  {
    ret = MngClt_ParamErr; 
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func KeyMng_ShmWrite() err:");
    goto END;
  }

  //获得共享内存
  ret = IPC_MapShm(shmhdl,(void**)&addr);
  if(addr == NULL)
  {
    printf("addr NULL\n");
    goto  END;
  }
  if(ret != 0)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"func IPC_MapShm() err:");
    goto END;
  }
    for(i = 0; i < maxnodenum; i++)
    {
     /*printf("%d\n",maxnodenum);*/
     CurNode = (NodeSHMInfo*)(addr + i * sizeof(NodeSHMInfo));
    if(strcmp(pNodeInfo->serverId,CurNode->clientId) == 0 &&
        strcmp(pNodeInfo->clientId,CurNode->clientId) == 0)
    {
      // 更新密钥数据
      memcpy(CurNode,pNodeInfo,sizeof(NodeSHMInfo));
      KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[2],ret,"网点密钥已经存在,已重新覆盖密钥信息");
      goto END;
    }
    }
  for(i = 0; i < maxnodenum; i++)
  {
    CurNode = (NodeSHMInfo*)addr + i*sizeof(NodeSHMInfo);
    if(memcmp(CurNode,&ZeroNode,sizeof(NodeSHMInfo)) == 0)
    {
      //新加入的网点信息
      memcpy(pNodeInfo,CurNode,sizeof(NodeSHMInfo));
      KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[2],ret,"插入新的网点信息\n");
      goto END;
    }
  }
  if(i == maxnodenum)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"网点信息已满\n");
    goto END;
  }
END:
  if(addr != NULL) IPC_UnMapShm(addr);
  return ret;
}
int KeyMng_ShmRead(int shmhdl, char *clientId, char *serverId,  int maxnodenum, NodeSHMInfo *pNodeInfo)
{
  int ret = 0, i = 0;
  NodeSHMInfo* CurNode = NULL;
  char* addr = NULL;
  if(clientId == NULL || serverId == NULL ||
      pNodeInfo == NULL)
  {
    ret = MngClt_ParamErr;
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"KeyMng_ShmRead() err %d\n",ret);
    goto END;
  }
  ret = IPC_MapShm(shmhdl,(void**)&addr);
  if(ret != 0)
  {
    KeyMng_Log(__FILE__,__LINE__,KeyMngLevel[4],ret,"IPC_MapShm() err %d\n",ret);
    goto END;
  }
  
  for(; i < maxnodenum; i++)
  {
    CurNode = (NodeSHMInfo*)addr + i * sizeof(NodeSHMInfo);
    if(CurNode->clientId == clientId &&
        CurNode->serverId == serverId)
    {
        printf("找到网点信息,开始进行拷贝\n");
        memcpy(pNodeInfo,CurNode,sizeof(NodeSHMInfo));
        goto END;
    }
  }
  printf("指定的网点信息不存在\n");
END:
  if(addr != NULL)
    IPC_UnMapShm(addr);
    return ret;
}
