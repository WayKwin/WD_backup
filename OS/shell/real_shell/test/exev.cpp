#include<stdio.h>
#include<unistd.h>
char* command = "ls";
char* parament[] = {"ls","-a"};
//char* parament[] = {"ls"};
int main()
{
  execvp(command,parament);
}
