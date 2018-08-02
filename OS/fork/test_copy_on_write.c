#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
  pid_t pid = fork();
  int num = 0;
  if(pid == 0)
  {
    printf("im child, num is : %d, address is : %p",num,&num);
  }
  else 
  {
    printf("im father, num is : %d, address is : %p",num,&num);
  }
  return 0;
  
}
