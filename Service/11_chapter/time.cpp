#include"time.h"
sort_timer_list::~sort_timer_list()
{
  while(head)
  {
    util_timer* to_delete = head;
    head = head->next;
    delete to_delete;
  }
}
void sort_timer_list::add_timer(util_timer&timer)
{
   if(head == NULL)
   {
      head = &timer;
      tail = &timer;
      return;
   }
   else 
   {
     if(timer.expire < head->expire)
     {
        timer.next = head;
        head->prev = &timer;
        head = &timer;
        return;
     }
     else if(timer.expire > tail->expire)
     {
       tail->next = &timer;
       timer.prev  =tail;
       tail = &timer;
       return;
     }
   }
   add_n_position(timer,head);
}
void sort_timer_list::del_timer(util_timer& timer)
{
  if(head == NULL)
    return;
  if(&timer == head && &timer == tail)
  {
      delete head;
      return;
  }
  else if(&timer == head)
  {
    util_timer* to_delete = &timer;
    head = head->next;
    head->prev = NULL;
    delete  to_delete;
  }
  else if(&timer == tail)
  {
    util_timer* to_delete = &timer;
    tail = tail->prev;
    tail->next = NULL;
    delete to_delete;
  }
  else 
  {
    timer.prev->next = timer.next;
    timer.next->prev = timer.prev;
    delete &timer;
  }
}
//双向链表的删除考虑 一个节点,是首节点,是尾节点,非首非尾的情况
void sort_timer_list::adjust_timer(util_timer& timer)
{
  //timer 值变大 
  util_timer* next = timer.next;
  if(!next || timer.expire < next->expire)
    return;
  if(&timer == head)
    {
        head = head->next;
        head->prev = NULL;
        add_n_position(timer,head);
    }
  else 
  {
   timer.prev->next = timer.next;
   timer.next->prev = timer.prev;
   add_n_position(timer,timer.next);
  }
}
void sort_timer_list::add_n_position(util_timer& timer,util_timer* head)
{
  while(head)
  {
    if(head->expire > timer.expire)
    {
      break;
    }
    head = head->next;
  }
  if(head == NULL)
  {
    // add 节点已经处理过这种情况,但是 adjust没有处理
    tail->next = &timer;
    timer.prev  =tail;
    tail = &timer;
    return;
  }
  util_timer* prev = head->prev;
  prev->next = &timer;
  timer.prev = prev;
  timer.next = head;
  head->prev = &timer;
}
void sort_timer_list::tick()
{
  if(!head)
  {
    return;
  }
  std::cout<< "timer tick" << std::endl;
  time_t cur = time(NULL);
  util_timer* tmp = head;
  while(tmp)
  {
    if(cur < tmp->expire)
    {
      break;
    }
    //第一个到期任务
    tmp->cb_func(tmp->user_data);
    //注意链表的是升序的
    head = tmp->next;
    if(head)
    {
      head->prev = NULL;
    }
    tmp = head;
  }
}
int main()
{

}
