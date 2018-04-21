#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#define ERR_EXIT(m)\
    do\
{\
    perroe(m);\
        exit(EXIT_FAILURE);\
}while(0)
#define CONSUMERS_COUNT 1
#define PRODUCERS_COUNT 1
#define BUFFSIZE 10
int g_buffer[BUFFSIZE];

//consumer_step``
unsigned short in = 0;
//producter_step
unsigned short out = 0;
unsigned short produce_id = 0;
unsigned short consume_id = 0;

sem_t g_sem_full;
sem_t g_sem_empty;
pthread_mutex_t g_mutex;

pthread_t g_thread[CONSUMERS_COUNT+PRODUCERS_COUNT];
void* consume(void* arg)
{
    int i;
    int num = *(int*) arg;
    free(arg);
    while(1)
    {
        printf("%d wait buffer not empty \n", num);
        //初始化为空的是数据, 消费者p 数据
        // 只要信号量变为 负数,这个线程就会被挂起
        sem_wait (&g_sem_empty);
        pthread_mutex_lock(&g_mutex);
        for( i = 0; i < BUFFSIZE; i++)
        {
            printf("%02d ", i);
            if( g_buffer[i] == -1 )
                printf("%s", "null");
            else
                printf("%d", g_buffer[i]);
            if( i == out )
                printf("\t<--consume");
            printf("\n");
        }
        consume_id = g_buffer[out];
        printf("%d end consuem product %d \n",num,consume_id);
        g_buffer[out] = -1;
        out = (out + 1) % BUFFSIZE;
        printf("%d end consume product %d\n", num, consume_id);
        pthread_mutex_unlock(&g_mutex);
        sem_post(&g_sem_full);
        sleep(1);
    }
}
void* product(void* arg)
{
    int i;
    int num = *(int*) arg;
    free(arg);
    while(1)
    {
        printf("%d wait buffer not full \n", num);
        sem_wait(&g_sem_full);
        pthread_mutex_lock(&g_mutex);
        //每次都打印队列状态
        for( i = 0; i < BUFFSIZE; i++ )
        {
            printf("%02d ", i);
            if( g_buffer[i] == -1 )
                printf("%s", "null");
            else
                printf("%d", g_buffer[i]);
            if( i == in )
                printf("\t<--produce");
            printf("\n");
        }
        printf("%d begin produce product %d\n", num, produce_id);
        g_buffer[in] = produce_id;
        in = (in + 1) % BUFFSIZE;
        printf("%d end produce product %d\n", num, produce_id++);
        pthread_mutex_unlock(&g_mutex);
        sem_post(&g_sem_empty);
        usleep(10000);
    }
    return NULL;
}
int main(void)
{
    int i;
    for( i = 0; i < BUFFSIZE; i++ )
    {
        g_buffer[i] = -1;
    }
    sem_init(&g_sem_full, 0, BUFFSIZE);
    sem_init(&g_sem_empty, 0, 0);
    for( i = 0; i < CONSUMERS_COUNT; i++ )
    {
        int *p = (int *) malloc(sizeof(int));
        *p = i;
        pthread_create(&g_thread[i], NULL, consume, p);
    }
    for( i = 0; i < PRODUCERS_COUNT; i++ )
    {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_create( &g_thread[i], NULL, product, p );
    }
    for(i = 0; i < PRODUCERS_COUNT + CONSUMERS_COUNT; i++)
    {
        pthread_join(g_thread[i], NULL);
    }
    sem_destroy(&g_sem_full);
    sem_destroy(&g_sem_empty);
    pthread_mutex_destroy(&g_mutex);
}

