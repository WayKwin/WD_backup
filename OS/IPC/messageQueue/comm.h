#ifndef _COMM_H_
#define _COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<fcntl.h>

//还必须是真的目录
#define PATHNAME "."
#define PROJ_ID 0x6324
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
struct msgbuf
{
    long mtype;
    char mtext[1024];
};
int creatMessageQueue();
int getMessageQueue();
int destoryMessageQueue(int msgid);
int sndMessage(int msgid, int who,char* send_msg);
int recMessage(int msgid,int recType,char* rec_msg);

#endif



