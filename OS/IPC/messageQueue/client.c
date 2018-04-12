#include"comm.h"

int main()
{
    int msgid =  getMessageQueue();
    char buf[1024];
    while(1)
    {
        printf("plase entry :");
        fflush(stdout);
        ssize_t s  = read(0, buf, sizeof(buf) - 1);
        if(s > 0)
        {
            buf[s] = 0;
            sndMessage(msgid,CLIENT_TYPE,buf);
            printf("send done,wait recv...\n");
        }
        recMessage(msgid,SERVER_TYPE,buf);
        if(strcmp(buf,"quit\n") == 0 )
        {
            printf("Server has been disconnection \n");
            break;
        }
        printf("Server: %s\n",buf);
    }
    destoryMessageQueue(msgid);
    return 0;
}
