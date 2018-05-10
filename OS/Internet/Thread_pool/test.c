#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<malloc.h>
#define Pthread_Num 10
char* fun(void)
{
  return NULL;
}
int main()
{
  char* (*p)(void);
  p = fun;
  free((void*)p);
  printf("%lu\n", sizeof(p));
}
