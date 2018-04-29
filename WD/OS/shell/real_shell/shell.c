#include"shell.h"
char prompt[MAX_PROMPT];
struct parse_info info;
//提示符只是在read_command 函数有用
char** command = NULL;
char** parameters;
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
        int pipe_fd[2] ,int_fd, out_fd;
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
        //执行命令子进程
        if( (child1 = fork()) != 0 )
        {
            if(info.flag & IS_PIPED)
            {
                 //管道 a|b  执行b的子进程
                //此时的fork ? 假设a是bash c_a1是第一次fork用来执行指令的.第二次的fork a会fork出 c_a2, c_a1又会fork出 cc_a1
                // 应该是 c_a1fork出cc_a1就行了 ?
                // 加上(chil1 == 0 )?
                //子进程的子进程
                if((child2 = fork()) != 0)
                {
                    dup2(pipe_fd[0],fileno(stdin) );
                    close(pipe_fd[1]);
                    close(pipe_fd[0]);
                    execvp(info.command2,info.parameters2);
                }
                else
                {
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                    waitpid(child2, &status, 0);
                }
            }
            if(info.flag & BACKGROUND)
            {

            }
            execvp(*command,parameters);
        }
        else if(child1 == 0)
        {

        }

    }
}
