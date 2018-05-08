#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
void handler_sigchild()
{
    int pid ;
    while(pid = waitpid(-1, NULL, WNOHANG) >0 )
    {
        printf(" wait success\n");
    }
    printf("child quit");
}
int main()
{
    signal(SIGCHLD,handler_sigchild);
    pid_t pid;
    int i;
    for(; i < 5; i++)
    {
        pid = fork();
        if( pid == 0 )
        {
            printf(" child dong someting\n");
            sleep(1);
            exit(1);
        }
        if( pid > 0 )
        {
            printf("father doing something");
            sleep(2);
        }
    }
}
