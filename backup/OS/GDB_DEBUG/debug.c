#include<stdio.h>
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
}
void process_child()
{
    pid_t pid = getpid();

}
