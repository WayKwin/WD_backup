#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t id;
char *ps[8] = {
    "ps",
    "axj",
    NULL
};
char *grep[8] = {
    "grep",
    /*".",*/
    "sleep 1000",
    NULL
};
int main()
{
    int fd[2];
    pipe(fd);
    int pid_1,pid_2;
    pid_1 = fork();

    //父进程
    if( pid_1 != 0 )
    {
        pid_2 = fork();
        //子进程1j
        if(pid_2 == 0)
        {
            close(fd[1]);
            /*close(0);*/
            dup2(fd[0],0);
            close(fd[0]);
            execvp("grep",grep);
        }
        else
        {
            close(fd[0]);
            close(fd[1]);
            waitpid(-1, 0, 0);
        }
    }
    else
    {
        //子进程2
        close(fd[0]);
        /*close(fd[1]);*/
        close(1);
        dup2(fd[1],1);
        close(fd[1]);
        execvp("ps",ps);
    }
    return 0;
}
