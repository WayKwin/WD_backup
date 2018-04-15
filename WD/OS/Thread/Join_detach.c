#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int retval = 0;
void* pthread_fun1(void* arg)
{
    pthread_t* thread_id = (pthread_t* )arg;
    int cnt = 3;
    while(cnt --)
    {
        printf("thread 1 : %0x cnt %d\n ",thread_id, cnt);
        sleep(1);

    }
    retval = 1;
    return (void*) &retval;
}
void* pthread_fun2(void* arg)
{
    //分离进程2
    pthread_detach(pthread_self());

    pthread_t* thread_id = (pthread_t* )arg;
    int cnt  = 3;
    while(cnt --)
    {
        printf("thread2 : %0x cnt:%d \n",thread_id, cnt);
        sleep(1);
    }
    return (void*) &retval;
}

int main()
{
    pthread_t main_thread, thread1,thread2;
    pthread_create(&thread1,NULL,pthread_fun1,(void *) &thread1);

    pthread_create(&thread2,NULL,pthread_fun2,(void *) &thread2);
    main_thread = pthread_self();
    while(1)
    {
        void  *ret;
        int ret1 = pthread_join(thread1,&ret);
        //阻塞式等待
        int ret2 = pthread_join(thread2,NULL);
        printf("main thread  %0x wait thread1 %0x wait 1 status : %d wait thread2 %0x wait 2 status :%d\n",
                main_thread,thread1, ret1,thread2,ret2);
        printf("%d\n",*(int* )ret);
        sleep(1);
    }

}
