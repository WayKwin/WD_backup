#include<stdio.h>
enum CTYPE{COREA,COREB};
class SingleCore 
{
  public:
    virtual void Show() = 0;
};
class SingleCoreA: public SingleCore 
{
  public:
    void Show() 
    {
        printf("SingleCore A called \n");
    }
};
class SingleCoreB: public SingleCore 
{
  public:
    void Show()
    {
      printf("SingleCore B called \n");
    }
};
class Factory:public SingleCore 
{
  public:
    SingleCore* produce(CTYPE type)
    {
        switch(type)
        {
          case COREA:
            return new SingleCoreA();
          case COREB:
            return new SingleCoreB();
        }
    }
};
