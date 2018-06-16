//饿汉模式,已经提前创建好了实例,那么就是线程安全的
class Singleton
{
  public:
  static Singleton* getInstance();
  private:
    Singleton();
    Singleton(Singleton& s);
    ~Singleton();
    static Singleton* OneInstance;
};
Singleton* Singleton::OneInstance = new Singleton();
 Singleton* Singleton::getInstance()
{
    return OneInstance;
};
int main()
{

}
