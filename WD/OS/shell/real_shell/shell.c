#include"shell.h"
char prompt[MAX_PROMPT];
struct parse_info info;
//提示符只是在read_command 函数有用
char** command = NULL;
char** parameters = NULL;
//命令和参数有多个函数要用
void proc()
{
    command = (char ** )malloc(sizeof(char*)* MAXARG);
    parameters = (char ** )malloc(sizeof(char*)* MAXARG);
    int para_num ;
    //子进程的退出状态
    int status;
    if( command == NULL || parameters == NULL )
    {
        perror("malloc filed:");
        return;
    }
    pid_t child1,child2;
    while(1)
    {
        int pipe_fd[2] ,in_fd, out_fd;
        type_prompt(promopt);
        int para_num = read_command(command,parameters,promopt);
        if( para_num == -1 )
            continue;
        parsing(parameters,para_num, &info);
        if( (info.flag & IS_PIPED) == 1 )
        {
            if(pipe(pipe_fd) < 0)
            {
                perror("pipe falied :");
            }
        }
        //父进程  等会要循环等待的那个
        if( (child1 = fork()) != 0 )
        {
            if(info.flag & IS_PIPED)
            {
                if((child2 = fork()) == 0)
                {
                    //新的子进程
                    dup2(pipe_fd[0],fileno(stdin) );
                    close(pipe_fd[1]);
                    close(pipe_fd[0]);
                    execvp(info.command2,info.parameters2);
                }
                else
                {
                    //父进程
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                    waitpid(child2, &status, 0);
                }
            }
            if(info.flag & BACKGROUND)
            {
                   //TODO
                printf("todo\n");
            }
            else
            {
                waitpid(child1, NULL, 0);
            }
        }
        //child == 0
        else if( child1 == 0 )
        {
            if( info.flag & IS_PIPED )
            {
                //如果只有管道
                if(!(info.flag & OUT_REDIRECT) && !(info.flag & OUT_REDIRECT_APPEND))
                {
                    close(pipe_fd[0]);
                    close(fileno(stdout));
                    dup2(pipe_fd[1],fileno(stdout));
                    close(pipe_fd[1]);
                }
                else//有管道和重定向的情况下关闭管道
                {
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);//发送SISGPIPE破坏管道
                    if( info.flag & OUT_REDIRECT )
                    {
                        out_fd = open(info.out_file, O_WRONLY | O_CREAT | O_TRUNC,0666);
                    }
                    else
                    {
                        out_fd = open(info.out_file, O_WRONLY | O_APPEND| O_TRUNC,0666);
                    }
                    close(fileno(stdout));
                    dup2(out_fd,fileno(stdout));
                    close(out_fd);
                }
            }
            //没有管道 的情况
            else
            {
                if(info.flag & OUT_REDIRECT)
                {
                    out_fd = open(info.out_file, O_WRONLY | O_CREAT | O_TRUNC,0666);
                    close(fileno(stdout));
                    dup2(out_fd,fileno(stdout));
                    close(out_fd);
                }
                if(info.flag & OUT_REDIRECT_APPEND)
                {
                    out_fd = open(info.out_file, O_WRONLY | O_APPEND| O_TRUNC,0666);
                    close(fileno(stdout));
                    dup2(out_fd,fileno(stdout));
                    close(out_fd);
                }
            }
            if(info.flag & IN_REDIRECT)
            {
                in_fd = open(info.in_file, O_WRONLY | O_CREAT | O_TRUNC,0666);
                close(fileno(stdin));
                dup2(in_fd,fileno(stdin));
                close(in_fd);
            }
            if(info.flag & IN_REDIRECT_APPEND)
            {
                in_fd = open(info.in_file, O_WRONLY | O_APPEND | O_TRUNC,0666);
                close(fileno(stdin));
                dup2(in_fd,fileno(stdin));
                close(in_fd);
            }
            execvp(*command,parameters);
        }

    }
}
int main()
{
    proc();
    return 0;
}
