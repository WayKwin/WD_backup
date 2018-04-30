#include"shell.h"
void parse_info_init(struct parse_info *info)
{
    info->flag = 0;
    info->in_file = NULL;
    info->out_file = NULL;
    info->command2 = NULL;
    info->parameters2 = NULL;
}
int parsing(char** parameters,int parse_num, struct parse_info* info)
{
    if(parse_num == 0)
        return 0;
    if( strcmp( parameters[parse_num - 1], "&" ) == 0)
    {
        info->flag |= BACKGROUND;
        // 注意把 & 结束后还得把参数数目 - 1
        parameters[ --parse_num ] = NULL;
    }
    int i = 0;
    //注意这里for循环不能i++
    for( ; i < parse_num; )
    {
        if( strcmp(parameters[i], ">") == 0   )
        {
            info->flag |= IN_REDIRECT;
            info->in_file = parameters[i + 1];
            parameters[i] = NULL;
            //跳过 >和 in_file
            i += 2;
        }
        else if( strcmp(parameters[i], ">>") == 0   )
        {
            info->flag |= IN_REDIRECT_APPEND;
            info->in_file = parameters[i + 1];
            parameters[i] = NULL;
            i += 2;
        }
        else if( strcmp(parameters[i], "<") == 0   )
        {
            info->flag |= OUT_REDIRECT_APPEND;
            info->out_file = parameters[i + 1];
            parameters[i] = NULL;
            i += 2;
        }
        else if( strcmp(parameters[i], "<<") == 0   )
        {
            info->flag |= OUT_REDIRECT_APPEND;
            info->out_file = parameters[i + 1];
            parameters[i] = NULL;
            i += 2;
        }
        //bug//暂不处理管道
        else if( strcmp(parameters[i], "|") == 0 )
        {
            info->flag |= IS_PIPED;
            //管道后的command 和 parameter2
            info->command2 = parameters[i + 1];
            if( parameters[i + 1] )
            info->parameters2 = &parameters[i + 1] ;
            //跳过指令待定
            i += 1;
            //unfish
            //
        }
        else
            i++;
    }
#ifdef DEBUG
    printf("PARSING DEBUG: \n");
    printf("\nbackground:%s \n",(info->flag & BACKGROUND? "yes" : " NO "));
    printf("in redirect :");
    info->flag & IN_REDIRECT ? printf("yes,in_file:%s\n",info->in_file) : printf("No\n");
    printf("in redirect append :");
    info->flag & IN_REDIRECT_APPEND ? printf("yes,in_file:%s\n",info->in_file) : printf("No\n");
    printf("out redirec:");
    info->flag & OUT_REDIRECT? printf("yes,out_file:%s\n",info->out_file) : printf("No\n");
    printf("out redirect append :");
    info->flag & OUT_REDIRECT_APPEND ? printf("yes,out_file:%s\n",info->out_file) : printf("No\n");
    printf("pipe :");
    if(info->flag & IS_PIPED)
    {
        printf("yes, command2 : %s\n" ,info->command2);
        int i = 0;
        printf("parameters2[] :");
        while(info->parameters2[i])
        {
            printf("%s",info->parameters2[i]);
            i++;
        }
        printf("\n");

    }
    else
    printf("No\n");
#endif

    return 0;
}
#ifdef DEBUG_PARSING
    struct parse_info info;
    char buff[256];
    char* command[100];
    char* parameters[100];
int main()
{
    while(1)
    {
        type_prompt(buff);
        int ret =  read_command(command,parameters,buff);
        parsing(parameters,ret, &info);
    }

}
#endif
