#include"comm.h"
int main()
{
    int msgid = creatMessageQueue();
    char buf[1024];
    while(1)
    {
        recMessage(msgid,CLIENT_TYPE,buf);
        //注意我们习惯使用 回车结束 而不是c-d
        if( strcmp(buf,"quit\n") == 0 )
        {
            printf("Client has been  disconnection\n");
            break;
        }
        printf("Client: %s\n",buf);
        printf("plase entry :");
        fflush(stdout);
        ssize_t s  = read(0, buf, sizeof(buf) - 1);
        if(s > 0)
        {
            buf[s] = 0;
            sndMessage(msgid,SERVER_TYPE,buf);
            printf("send done,wait recv...\n");
        }
    }
    destoryMessageQueue(msgid);
    return 0;
}
