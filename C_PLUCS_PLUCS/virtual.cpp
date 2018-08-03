#include<stdio.h>
class Virtual_Class
{
  public:
  virtual void Virtual_fun(); 
};
class Non_Virtual_Class
{
  public:
  void Non_Virtual_fun(); 
};
void Virtual_Class::Virtual_fun()
{
  int a = 10;
}
Virtual_Class a;
Non_Virtual_Class b;
