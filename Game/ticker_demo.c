#include<stdio.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int set_ticker(int n_msecs);
int main()
{
  void countdown(int);
  signal(SIGALRM,countdown);
  if((set_ticker(500) == -1))
    perror("set_ticker");
  else 
    while(1)
    {
      /*pause();*/
      sleep(1);
      printf("hello world");
    }
  return 0;
}
void countdown(int sigum)
{
  static int num = 10;
  printf("%d ..", num--);
  fflush(stdout);
  if( num < 0 )
  {
    printf("DONE! \n");
    exit(0);
  }
}
int set_ticker(int n_msecs)
{
  struct itimerval new_timeset;
  long n_sec,n_usecs;

  //秒等于毫秒/1000
  n_sec = n_msecs / 1000;
  // 1400  1000毫秒和 400 微秒 
  // 计时器分两部分, 一部分是 毫秒,另一部分是 毫秒表示完了之后的微秒
  n_usecs = (n_msecs % 1000) * 1000L;
  new_timeset.it_interval.tv_sec = n_sec;
  new_timeset.it_interval.tv_usec = n_usecs;

  new_timeset.it_value.tv_sec = n_sec;
  new_timeset.it_value.tv_usec = n_usecs;

  return setitimer(ITIMER_REAL, & new_timeset, NULL);
}
