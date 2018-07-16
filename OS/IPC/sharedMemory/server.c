#include"comm.h"
int main()
{
    int shmid = createShm(4096);
    //
    char* addr = (char*)shmat(shmid,NULL,0);
    sleep(2);
    int i = 0;
    while(i++ < 26)
    {
        printf("%s\r",addr);
        fflush(stdout);
        /*printf("1\n");*/
        sleep(1);
    }
    shmdt(addr);
    destroyShm(shmid);
    sleep(2);
    return 0;
}
