#ifndef LOCKER_H
#define LOCKER_H
#include<pthread.h>
#include<exception>
#include<list>
#include<semaphore.h>
// TODO
// 是否要单例模式?线程安全?

class sem 
{
  public:
  sem()
  {
    if(sem_init(&s_sem,0,0) < 0)
    {
      throw  std::exception();
    }
  }
  ~sem()
  {
    if(sem_init(&s_sem,0,0) < 0)
    {
      throw std::exception();
    }
  }
  bool p()
  {
    return sem_wait(&s_sem);
  }
  bool v()
  {
    return sem_post(&s_sem);
  }
  private:
    sem_t s_sem;
};

class locker
{
public:
  locker()
  {
    if(pthread_mutex_init(&l_mutex,NULL) != 0)
    {
      throw std::exception();
    }
  }
  ~locker()
  {
    if(pthread_mutex_destroy(&l_mutex) != 0)
    {
      throw  std::exception();
    }
  }
  bool lock()
  {
    return pthread_mutex_lock(&l_mutex);
  }
  bool unlock()
  {
    return pthread_mutex_unlock(&l_mutex);
  }
private:
  pthread_mutex_t  l_mutex;
};
class cond 
{
  public:
    cond()
    {
        if( pthread_mutex_init(&c_mutex, NULL) != 0 )
        {
            throw std::exception();
        }
        if ( pthread_cond_init(&c_cond, NULL) != 0 )
        {
           // 注意 cond_init  失败后应该摧毁 c_mutex
            pthread_mutex_destroy( &c_mutex);
            throw std::exception();
        }
    }
    ~cond()
    {
        if( pthread_mutex_destroy(&c_mutex) != 0 )
        {
            throw std::exception();
        }
        if ( pthread_cond_destroy(&c_cond) != 0 )
        {
            pthread_mutex_destroy(&c_mutex);
            throw std::exception();
        }
    }
    bool wait()
    {
      int ret;
      if(( ret = pthread_mutex_lock(&c_mutex )) < 0)
      {
          return ret; 
      }
      return pthread_cond_wait(&c_cond,&c_mutex);
    }
  private:
    pthread_cond_t c_cond;
    pthread_mutex_t c_mutex;
};

#endif
