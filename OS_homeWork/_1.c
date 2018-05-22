#include<stdio.h>
#include<stdlib.h>
#define R 1
#define E 0
typedef struct PCB
{
  int pid;
  //优先级
  int priority;
  //运行时间
  int time;
  //程序状态
  int flag;
  struct PCB* next;
  struct PCB* prev;
}PCB;
// 进程初始化
void ProcessInit(PCB** head)
{
  if(head == NULL)
    return;
  PCB* NewProcess = (PCB*)malloc(sizeof(PCB));
  printf("please enter : pid\n");
  scanf("%d",&(NewProcess->pid));
  printf("please enter : priority \n");
  scanf("%d",&(NewProcess->priority));
  printf("please enter: running time\n ");
  scanf("%d",&(NewProcess->time));
  NewProcess->next = NULL;
  NewProcess->flag = R;
  if(*head == NULL)
  {
    *head = NewProcess;
  }
  else 
  {
    PCB* cur = *head;
    while( cur->next)
    {
      cur = cur->next;
    }
    cur->next = NewProcess;
    NewProcess->prev = cur;
    NewProcess->next = NULL;
  }
}
void ProcessSort(PCB* phead)
{
  PCB* start = phead;
  PCB* end = NULL;
  while(start != end)
  {
    PCB* i;
      
    for(i = start; i->next != end; i = i ->next)
    {
      if( i->priority < i->next->priority)
      {
        PCB* i_next = i->next;
        PCB* i_next_next = i->next->next;
        PCB tmp = *i;
        *i = *(i->next); 
        i->next = i_next; 
        *(i->next) = tmp;
        i->next->next = i_next_next;
        /*PCB*  i_next = i ->next;*/
        /*i->next = i_next ->next;*/
        /*i_next->next = i;*/
      }
    }
    end = i;
  }
}
void Run(PCB** phead)
{
  PCB* head = *phead;
  if(head == NULL)
    return;
  PCB* to_run = head;
  to_run->time -= 1;
  to_run->priority -= 1;
  //如果队列有下一个元素
  if((*phead)->next)
    *phead= (*phead)->next;
  //否则让其等于正在运行的程序(本身)
  else 
  {
    //如果运行的程序也结束了,将头指置NULL
    if(to_run->time  <= 0)
    {
      free(to_run);
      to_run = NULL;
      (*phead) = to_run;
      return;
    }
    (*phead) = to_run;
    return;
  }
  //如果运行进程状态为空 ,将其出对列
  if(to_run->priority <= 0 &&  to_run->time  <= 0)
  {
    free(to_run);
    to_run = NULL;
    return;
  }
  //不为空,将其加入队列
  PCB* cur = *phead;
  while(cur->next)
  {
    cur = cur->next;
  }
  cur->next = to_run;
  to_run->next = NULL;
}
void PrintRunnignStatus(PCB** head)
{
  PCB* cur = *head;
  printf("初始状态为\n");
  while(cur)
  {
    printf( "[pid %d , priority:%d time :%d ]", cur->pid,cur->priority,cur->time); 
    cur = cur->next;
  }
  printf("\n"); 
  while(*head)
  {
    Run(head);
    if(*head != NULL)
    printf("运行状态为\n");
    {
      cur = *head;
      while(cur)
      {
      printf( "[pid %d , priority:%d time :%d ]", cur->pid,cur->priority,cur->time); 
        cur = cur->next;
      }
      printf("\n");
    }
  }
}
int main()
{
  PCB* head = NULL;
  printf("plase enter Process number\n");
  int max;
  scanf("%d",&max);
  int i = 0;
  for(; i < max; i++)
  {
    ProcessInit(&head);  
  }
  ProcessSort(head);
  while(head)
  {
    printf(" %d",head->priority);
    head = head->next;
  }
  printf("\n");
  PrintRunnignStatus(&head);
  return 0;
}
