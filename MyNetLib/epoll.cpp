#include"epoll.h"
#include<fcntl.h>
#include<unistd.h>
#include<memory>
using namespace::netlib;
Epoll::Epoll(int conn_size):_maxEvents(conn_size),_et(true),_oneshot(false)
{
  _epollFd = epoll_create(1024);
  _readyQueue = NULL; 
  if(_readyQueue != NULL)
  {
    delete[] _readyQueue;
  }
  _readyQueue = new epoll_event[_maxEvents + 1];
}
Epoll::~Epoll()
{
  if(_readyQueue != NULL)
  {
    delete[] _readyQueue;
    _readyQueue = NULL;
  }
  close(_epollFd);
}
void Epoll::SetNonBlocking(int fd)
{
  int old_status = fcntl(fd,F_GETFL); 
  int new_status = old_status | O_NONBLOCK;
  if(fcntl(fd,F_SETFL,new_status) < 0)
  {
    throw "fcntl error\n";
  }
}
void Epoll::AddFd(int fd)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = EPOLLIN  | EPOLLET;
 if( epoll_ctl(_epollFd,EPOLL_CTL_ADD,fd,&ev) < 0)
 {
   throw  "epoll_ctl add \n";
 }
 SetNonBlocking(fd);
}
void Epoll::Chmod(int fd,int events)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = events; 
  if(epoll_ctl(_epollFd,EPOLL_CTL_MOD,fd,&ev) < 0)
  {
    throw "epoll_ctl add \n";
  }
}
void Epoll::Addmod(int fd,int events)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events |= events; 
  if(epoll_ctl(_epollFd,EPOLL_CTL_MOD,fd,&ev) < 0)
  {
    throw "epoll_ctl chmod \n";
  }
}
int Epoll::wait()
{
  int readyNum = epoll_wait(_epollFd,_readyQueue,_maxEvents,-1);
  return readyNum;
}

