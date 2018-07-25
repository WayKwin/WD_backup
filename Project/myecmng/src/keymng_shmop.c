#include "../incl/myipc_shm.h"
#include"../incl/keymng_shmop.h"
#include"../incl/keymnglog.h"

int  KeyMng_ShmInit(int key,int maxnodenum,int * shmhdl)
{
  int ret = 0;
  void *mapddr = NULL;
  ret = IPC_OpenShm(key,sizeof(NodeSHMInfo)*maxnodenum,shmhdl);
  // 存在共享内存
  if(ret == MYIPC_NotEXISTErr)
  {
    //不存在
    ret = IPC_CreatShm(key,sizeof(NodeSHMInfo)*maxnodenum,shmhdl);
    if(ret != 0)
    {
      //创建失败
    }
    else 
    {
      //映射内存
        ret = IPC_MapShm(*shmhdl,&mapddr);
        if(ret != 0)
        {
          // 映射共享内存失败
          return ret;
        }
        memset(mapddr,0,sizeof(NodeSHMInfo)*maxnodenum);
        ret = IPC_UnMapShm(mapddr);
    }
  }
  // 有旧的共享内存,使用旧的
  else if (ret == 0)
  {
    /*printf("")*/
  }
  else 
  {
    // 失败
  }

  
}
