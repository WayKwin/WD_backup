#include"comm.h"
static int  messageGet(int flags)
{
    //收发方统一的key 找到统一的队列
    key_t _key = ftok(PATHNAME,PROJ_ID);
    if(_key < 0)
    {
        perror("ftok");
        return -1;
    }
    int msgid = msgget(_key,flags);
    if(msgid < 0)
    {
        perror("msgid");
        return -1;
    }
    return msgid;
}
int creatMessageQueue()
{
    return messageGet(IPC_CREAT | IPC_EXCL);
}
int getMessageQueue()
{
    return messageGet(IPC_CREAT);
}
int destoryMessageQueue(int msgid)
{
    if(msgctl(msgid, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        return -1;
    }
}
int sndMessage(int msgid, int whom, char *send_msg)
{
    struct msgbuf buf;
    buf.mtype = whom;
    strcpy(buf.mtext,send_msg);
    // 往哪发,发谁,发多少, 标志位
    if( msgsnd(msgid,&buf,sizeof(buf.mtext), 0) < 0 )
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}
int recMessage(int msgid, int recvType, char* recv_msg)
{
    struct msgbuf buf;
    if( msgrcv(msgid, (void *)&buf, sizeof(buf.mtext), recvType, 0 ) < 0)
    {
        perror("msgrcv");
        return -1;
    }
    strcpy(recv_msg,buf.mtext);
}

