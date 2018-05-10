#include"comm.h"
int main()
{
    int shmid = getShm(4096);
    //
    char* addr = shmat(shmid,NULL,0);
    int i = 0;
    sleep(2);
    while(i < 27)
    {
        addr[i] = 'a' + i;
        i++;
         //a0   ab0
        addr[i] = 0;
        sleep(1);
    }
    shmdt(addr);
    sleep(2);
    return 0;
}
