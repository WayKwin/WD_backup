#include"../epoll.h"
#include<string>
class Clinet
{
public:
  Clinet();
private:
  void StartUp();
  void GetConnection();
  void MessageCallBack();
  std::string _ip;
  int _port;
  
  
  
};
