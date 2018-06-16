#ifndef LST_TIMER
#define LST_TIMER
#include<time.h>
#include<iostream>
#include<netinet/in.h>
#define BUFFER_SIZE 64
struct util_timer;
struct client_data
{
  sockaddr_in address;
  int sockfd;
  char buf[BUFFER_SIZE];
  util_timer* timer;
};
struct util_timer
{
  public:
  util_timer():prev(NULL),next(NULL){}
  time_t expire;
  void (*cb_func) (client_data*);
  client_data* user_data;
  util_timer* prev;
  util_timer* next;
};
class sort_timer_list
{
  public:
  sort_timer_list():head(NULL),tail(NULL){}
  ~sort_timer_list();
  void add_timer(util_timer& timer);
  void del_timer(util_timer& timer);
  void adjust_timer(util_timer& timer);
  void tick();
  private:
  void add_n_position(util_timer& timer,util_timer* head);
  util_timer* head;
  util_timer* tail;
};

#endif
