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
    if( strcmp( parameters[parse_num - 1], "&" ) == 0)
    {
        info->flag |= BACKGROUND;
        parameters[ parse_num -1 ] = NULL;
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
        else if( strcmp(parameters[i], "|") == 0 )
        {
            info->flag |= IS_PIPED;
            //管道后的command 和 parameter2
            info->command2 = parameters[i + 1];
            info->parameters2 = &parameters[i + 1];
            //unfish
        }
    }
}
