#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
typedef struct arg_srtuct
{
    int *arg1;
    int *arg2;
    pthread_t* pthread_id;
}arg_struct;
void* pthread_fun(void * arg)
{
    arg_struct* argc = (arg_struct *)arg;
    while(1)
    {
        printf("pthread_id :%lu\n",argc->pthread_id);
    }
}
int main()
{
    arg_struct arg;
   int ret =  pthread_create(arg.pthread_id, NULL,pthread_fun,&arg);
   sleep(2);
    printf("%d",ret);
}
