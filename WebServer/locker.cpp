#include"locker.h"
  sem::sem()
  {
    if(sem_init(&s_sem,0,0) < 0)
    {
      throw  std::exception();
    }
  }
  sem::~sem() 
  {
    if(sem_init(&s_sem,0,0) < 0)
    {
      throw std::exception();
    }
  }
  bool sem:: p()
  {
    return sem_wait(&s_sem);
  }
  bool sem::v()
  {
    return sem_post(&s_sem);
  }
locker::locker()
  {
    if(pthread_mutex_init(&l_mutex,NULL) != 0)
    {
      throw std::exception();
    }
  }
locker:: ~locker()
  {
    if(pthread_mutex_destroy(&l_mutex) != 0)
    {
      throw  std::exception();
    }
  }
  bool locker::lock()
  {
    return pthread_mutex_lock(&l_mutex);
  }
  bool locker::unlock()
  {
    return pthread_mutex_unlock(&l_mutex);
  }
  cond::cond()
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
  cond::~cond()
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
  bool cond::wait()
  {
    int ret;
    if(( ret = pthread_mutex_lock(&c_mutex )) < 0)
    {
        return ret; 
    }
    return pthread_cond_wait(&c_cond,&c_mutex);
  }
  bool cond::wakeup()
  {
    return pthread_cond_signal(&c_cond);
  }
