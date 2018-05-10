#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#define Pthread_Num 10
typedef void* Process_arg;
typedef void*(*p_Process)(Process_arg arg) ;
typedef struct _Mission
{
    p_Process p;
    Process_arg arg;
    struct _Mission *next;
}Mission;
typedef struct _Tread_pool
{
    int shutdown;
    Mission* Mission_head;
    pthread_mutex_t GetMission_mutex;
    pthread_cond_t Mission_ready;
    pthread_t *pthread_ID;
    int MaxPthread_Num;
    int MissionNum;
}Thread_Pool;
int addr_Mission(p_Process ps, Process_arg arg);
void *thread_routine(void * arg);
void Thread_PoolInit(Thread_Pool* tp)
{
    if(tp == NULL)
        return;
    tp = (Thread_Pool*)malloc(sizeof(Thread_Pool));
    tp->shutdown = 0;
    tp->Mission_head = NULL;
    pthread_mutex_init(&(tp->GetMission_mutex ), NULL);
    pthread_cond_init(&(tp->Mission_ready ), NULL);
    tp->MaxPthread_Num = Pthread_Num;
    tp->thread_ID = (pthread_t *) malloc(sizeof(thread_ID));

}

