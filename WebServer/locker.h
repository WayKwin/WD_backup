#pragma  once
#include<pthread.h>
#include<exception>
#include<semaphore.h>

class sem 
{
  public:
  sem();
  ~sem();
  bool p();
  bool v();
  private:
    sem_t s_sem;
};

class locker
{
public:
  locker();
  ~locker();
  bool lock();
  bool unlock();
private:
  pthread_mutex_t  l_mutex;
};
class cond 
{
  public:
    cond();
    ~cond();
    bool wait();
    bool wakeup();
  private:
    pthread_cond_t c_cond;
    pthread_mutex_t c_mutex;
};

