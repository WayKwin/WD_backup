#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
void mydaemon()
{
    int i;
    int fd0;
    pid_t pid;
    struct sigaction sa;
    umask(0);
    if( ( pid = fork() ) < 0 )
    {
        perror("fork");
    }
    else if(pid > 0)
    {
        exit(0);
    }
    setsid();
    //忽略子进程退出状态也是处理信号的一种方法
    //避免子进程一直保持僵尸状态
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if( sigaction(SIGCHLD, &sa, NULL) < 0 )
    {
        return;
    }
    if( ( pid = fork() ) < 0 )
    {
       printf("fork error\n");
    }
    if( pid !=  0)
    {
        exit(0);
    }
    if( chdir("/") < 0 )
    {
        printf(" child dir error\n");
    }
    close(0);
    fd0 = open("/dev/null", O_RDWR);
    dup2(fd0,1);
    dup2(fd0,2);
}
int main()
{
    mydaemon();
    while(1)
    {
        sleep(1);
        //本来想让守护进程打印一句话
        //结果发现守护进程已经关闭stdout了
    }
}
