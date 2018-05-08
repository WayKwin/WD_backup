#ifndef __COMM_H__
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define PATHNAME "/usr/"
#define PROJ_ID 0x666
//通过flags确定是create还是get
//函数给出大小就行了
//返回值是commShm函数里的shmid
//重视封装
int createShm(int size);
int getShm(int size);
int destroyShm(int shmid);
//sharedMemoryAttach函数不用封装
#endif


