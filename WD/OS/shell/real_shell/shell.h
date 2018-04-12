#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_PROMPT 1024
#define MAXLINE 4096
#define MAXARG 20
//要先声明 这个结构体否则报警告
struct parse_info;
//获取 [@] 主机名和用户名
struct passwd *pwd;
//拼接头部
char promopt[256];
//输入型参数
void  type_prompt(char* prompt);
//此处应该统计parameters (命令)个数
int read_command(char** command, char** parameters, char *prompt);
//翻译
int parsing(char** parameters,int parse_num,struct parse_info* info);
//存入用户输入的指令
char buf[256];
//内建命令
int builtin_command(char* command,char** parameters);
//运行process
void proc();
//捕获信号
void sig_handler(int sig);
#ifndef STRUCT_PARSE_INFO
#define STRUCT_PARSE_INFO
#define BACKGROUND 1
#define IN_REDIRECT 2
#define IN_REDIRECT_APPEND 4
#define OUT_REDIRECT 8
#define OUT_REDIRECT_APPEND 16
#define IS_PIPED 32
typedef struct parse_info
{
    int flag;
    char* in_file;
    char* out_file;
    //为管道准备
    char* command2;
    char** parameters2;
}parse_infou;
#endif

