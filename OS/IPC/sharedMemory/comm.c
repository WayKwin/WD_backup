#include"comm.h"
static int commShm(size_t size,int flags)
{
    key_t key = ftok(PATHNAME,PROJ_ID);
    if(key < 0 )
    {
        perror("fork");
        return -1;
    }
    int shmid =  shmget(key,size,flags);
    if(shmid < 0)
    {
        perror("shmid");
        return -2;
    }
    return shmid;
}
int createShm(int size)
{
   return  commShm(size,IPC_CREAT|IPC_EXCL|0x666);
}
int getShm(int size)
{
    return commShm(size,IPC_CREAT);
}
int destroyShm(int shmid)
{
    if(shmctl(shmid,IPC_RMID,NULL) < 0)
    {
        perror("shmid");
        return -2;
    }
}
