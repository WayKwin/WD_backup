#include<sys/epoll.h>
#include<vector>

/** 
 * @brief  默认执行et, 所有文件描述符 非阻塞
 *  初始化时间:epollin
 */
namespace netlib
{
  class Epoll 
  {
    public:
      //阻塞
    Epoll() = default;
    Epoll(int MaxSize);
    ~Epoll();
    void SetNonBlocking(int fd); 
    //默认 epollin et
    void AddFd(int fd);
    void Chmod(int fd,int events);
    void Addmod(int fd,int events);
    void DelFd(int fd);
    void ChWorkStauts(int fd);
    int wait();
    private:
    int _epollFd;
    // 就绪队列长度
    int _maxEvents;
    bool _et;
    //线程竟态
    bool _oneshot;
    //就绪队列,epollwait返回用
    struct epoll_event* _readyQueue;
    //能不能定义一个结构体, 注册修改事件都用这一个结构体
    static struct epoll_event ev;
  };
}
