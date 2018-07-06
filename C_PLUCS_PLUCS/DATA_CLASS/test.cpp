class A 
{
  public:
  void fun(const A& a)
  {
    //a.fun2(*this);
  }
  void fun2(const A& a)
  {
    //a.num = 2;
  }
  int num;
};
int main()
{
  int a = 10;
  const int b = 20;
  int const *c = &a;
  const int &d = *c;
  if(d == *c)
  {

  }
}

