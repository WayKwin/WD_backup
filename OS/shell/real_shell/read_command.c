#include"shell.h"
/*#ifdef READLINE_ON*/
#include<readline/readline.h>
#include<readline/history.h>
/*#endif*/
//本来在头文件中 先要转移在proc中
//原版是用指针 所以不用buf
extern char buf[256];
/*int read_command(char* command[], char *parameters[], char *prompt)*/
int read_command(char** command, char *parameters[], char *prompt)
{
    memset(buf,0,sizeof(buf));
    strcpy(buf,readline(prompt));
    if(feof(stdin))
    {
        //readline不会把回车键的换行写入文本
        //write  写入buf会是  abcd\n\0的形式
        /*printf("\n");*/
        return 0;
    }
    if(buf[0] == '\0')
        return -1;
    int i = 0;
    int command_status = 0;
    //当 遇到第一个空格
    int parameter_status = 0;
    int parameters_count = 0;
    /*char argv[256];*/
    /*strcpy(argv,buf);*/
    for(i = 0;buf[i] == ' ';i++);
    for(; buf[i]; i++)
    {
        if(!isspace(buf[i]) && command_status == 0 )
        {
            /*command[command_count++] = buf + i;*/
            *command = buf + i;
            command_status = 1;
        }
        if(!isspace(buf[i]) && parameter_status == 0)
        {
            parameters[parameters_count++] = buf + i;
            parameter_status = 1;
        }
        if(isspace(buf[i]))
        {
            parameter_status= 0;
            buf[i] = '\0';
        }
    }
    parameters[parameters_count] = NULL;
#ifdef DEBUG
    printf("read_command debug: \n");
    printf("command[] = ");
    i = 0;
    /*while(command[i])*/
    /*{*/
        /*printf("%s ",command[i]);*/
        /*i++;*/
    /*}*/
    printf("%s ",command);

    i = 0;
    printf("\n");
    printf("parameters[] = ");
    while(parameters[i])
    {
        printf("%s ",parameters[i]);
        i++;
    }
    printf("\n");
    printf("parameters numbers: %d\n",parameters_count);
    printf("\n");
#endif
    if( *command == NULL )
        return -1;
    return parameters_count;
}
#ifdef DEBUG_READ_COMMAND
int main()
{
    char buff[256];
    char* a[100];
    char* b[100];
    while(1)
    {
        type_prompt(buff);
        read_command(a,b,buff);
    }
}
#endif
