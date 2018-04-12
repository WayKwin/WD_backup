#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
    char buf[64];
    int fd[2];
    int r = pipe(fd);
    if ( r == -1 )
    {
        perror("make pipe\n");
        return 2;
    }
    pid_t pid = fork();
    if( pid == 0 )
    {
        close(fd[0]);
        while(1)
        {
           int n =  read(0, buf,sizeof(buf) - 1);
           write(fd[1],buf,n);
        }
    }
    if( pid > 0  )
    {
            close(fd[1]);
            /*sleep(5);*/
            int cnt = 5;
            while(cnt--)
            {
                ssize_t s = read(fd[0],buf,sizeof(buf) - 1);
                buf[s] = '\0';
                printf("%s",buf);
            }
            close(fd[0]);
            /*sleep(5);*/
    }
    return 0;
}
