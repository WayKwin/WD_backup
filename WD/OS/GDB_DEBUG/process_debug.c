#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<wait.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
void process_child();
void process_father();

int main(int argc ,const char* argv[])
{
    pid_t pid;
    pid = fork();
    if( pid < 0 )
        perror("fork");
    if( pid == 0 )
        process_child();
    if( pid > 0 )
        process_father();
    return 0;
}
void process_child()
{
    pid_t pid = getpid();
    while(1)
    {

        sleep(1);
        printf(" im child  ID :[%d]\n",pid);
    }
}
void sig_handler( int SigNum )
{
    pid_t pid;
    while(( pid = waitpid(1, NULL, WNOHANG) ) > 0)
    {
        printf(" wait child  success! %d\n",pid);
    }
    printf("child is quit !\n");
}
void process_father()
{

    struct sigaction act ;
    act.sa_handler = sig_handler;
    sigaction(SIGCHLD, &act, NULL);
    pid_t pid = getpid();
    while(1)
    {
        sleep(1);
        printf(" im father ID :[%d]\n",pid);
    }
}
