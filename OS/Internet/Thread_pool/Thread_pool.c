#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<malloc.h>
#define Pthread_Num 3
typedef void* Process_arg;
typedef void*(*p_Process)(Process_arg arg) ;
typedef struct _Mission
{
    
    p_Process Mission_fun;
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
Thread_Pool* tp;
int addr_Mission(p_Process ps, Process_arg arg);
void *thread_routine(void * arg);
void Thread_PoolInit(Thread_Pool** t)
{
    if( t == NULL )
      return ;
    *t = (Thread_Pool*)malloc(sizeof(**t));
    Thread_Pool* tp = *t;
    tp = (Thread_Pool*)malloc(sizeof(Thread_Pool));
    tp->shutdown = 0;
    tp->Mission_head = NULL;
    pthread_mutex_init(&(tp->GetMission_mutex ), NULL);
    pthread_cond_init(&(tp->Mission_ready ), NULL);
    tp->MaxPthread_Num = Pthread_Num;
    tp->pthread_ID= (pthread_t *) malloc(sizeof(pthread_t)*tp->MaxPthread_Num);
    if(tp->pthread_ID == NULL)
      return;
    int i = 0;
    for( ; i < tp->MaxPthread_Num; i++ )
    {
      pthread_create(&(tp->pthread_ID[i]), NULL, thread_routine, NULL);
    }
}
void* thread_routine(void* arg)
{
  printf(" ID: %lu\n",pthread_self());
  while(1)
  {
    //线程只有两种状态 1. 执行任务,2,阻塞
    //在pool shutdown之前不会退出
   pthread_mutex_lock(&(tp->GetMission_mutex));
   if(tp->shutdown == 1)
   {
    printf("going to shutdown \n");
    pthread_mutex_unlock(&(tp->GetMission_mutex));
    pthread_exit(NULL);
    break;
   }
   while(tp->Mission_head == NULL)
   {
     printf("no Mission  i wait %lu\n",pthread_self());
     pthread_cond_wait(&(tp->Mission_ready), &(tp->GetMission_mutex));
   }  
   //将第一个任务出对列 
   Mission* to_run = tp->Mission_head;
   tp->Mission_head = tp->Mission_head->next;
   //取出任务后放锁
   pthread_mutex_unlock(&(tp->GetMission_mutex));
   //执行其中的函数
   (*(to_run->Mission_fun))(arg);
   //释放函数指针
   //free(to_run->Mission_fun);
   free(to_run);
   to_run = NULL;
  }
}

int add_Mission(p_Process ps, Process_arg arg)
{
  if(tp == NULL)
    return -1;
  pthread_mutex_lock(&(tp->GetMission_mutex));
  Mission* new_Mission = (Mission*) malloc(sizeof(Mission));
  if( new_Mission == NULL )
    return -1;
  new_Mission->Mission_fun = ps;
  new_Mission->arg = arg;
  new_Mission->next = NULL;
  if(tp->Mission_head == NULL)
  {
    tp->Mission_head = new_Mission;
  }
  else 
  tp->Mission_head->next = new_Mission;
  pthread_mutex_unlock(&(tp->GetMission_mutex));
  pthread_cond_signal(&(tp->Mission_ready));
  return 1;
}
void* my_porcess(void* arg)
{
  arg = (char*) arg;
  printf("im salt fish wuwuwu \n");
  sleep(2);
  return NULL;
}
void Thread_PoolDestroy(Thread_Pool* tp)
{

    if(tp == NULL)
      return ;
    //防止二次调用
    if( tp->shutdown == 1 )
      return;
    tp->shutdown = 1;
    //唤醒所有等待任务的线程
    pthread_cond_broadcast(&(tp->Mission_ready)); 
   int i = 0;
   for(; i < tp->MaxPthread_Num; i++)
   {
     pthread_join(tp->pthread_ID[i], NULL);
     free(tp->pthread_ID + i);
   }
    Mission* m = NULL;
    //清空链表
    while(tp->Mission_head)
    {
      m = tp->Mission_head;
      tp->Mission_head = tp->Mission_head->next;
      free(m);
      m = NULL;
    }
    pthread_mutex_destroy(&(tp->GetMission_mutex));
    pthread_cond_destroy(&(tp->Mission_ready));
    free(tp);
    tp = NULL;
 //   pthread_t* pt;
 //   while(tp->pthread_ID)
 //   {
 //    pt = tp->pthread_ID;
 //    free(pt);
 //    pt = NULL;
}

int main()
{
  //此处创建了3个线程
  Thread_PoolInit(&tp);
  int i;
  for( i = 0; i < 10; i ++ )
  {
    //加入任务后线程开始执行
    add_Mission(my_porcess, NULL);
  } 
  sleep(5);
  Thread_PoolDestroy(tp);
  printf("you running here \n");
  return 0;
}

