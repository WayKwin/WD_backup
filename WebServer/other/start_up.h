
/** 
 *  2018年6月13日 22:34:00
 *  TO_DO :回调通知函数
 */
#include<memory>
#include<string>
namespace netlib
{
  class StartUpLoop
  {
    public:
      StartUpLoop(std::string ip,int port);
      ~StartUpLoop();
      //创建监听套接字
      int CreateListenFd();
      //拿到连接后的处理(回调)
      void ConnectionHandle(int connfd);
      //TODO 回调函数的设置
    private:
      std::string _ip;
      int _port;
      int _listenFd;
  };
}
