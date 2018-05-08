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
struct passwd *pwd;
void type_prompt(char *);
