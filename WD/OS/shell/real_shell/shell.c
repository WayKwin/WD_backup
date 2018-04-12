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
    if( command == NULL || parameters == NULL )
    {
        perror("malloc filed:");
        return;
    }
    pid_t child1,child2;
    while(1)
    {
        int pid_fd[2] ,int_fd, out_fd;
        type_prompt(promopt);
        int para_num = read_command(command,parameters,promopt);
        if( para_num == -1 )
            continue;
        parsing(parameters,para_num, &info);
        if( (info.flag & IS_PIPED) == 1 )
        {
            if(pipe(pid_fd) < 0)  // eg  a|   ( command2 = NULL )
            {
                perror("pipe falied :");
            }
        }
        if( (child1 = fork()) != 0 )
        {
            if(info.flag & IS_PIPED)
            {

            }
        }
    }
}
