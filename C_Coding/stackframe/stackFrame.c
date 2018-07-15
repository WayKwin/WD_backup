#define MACRO 100

int myadd(int a,int b)
{
  static int INITIALIZED_STATIC_LOCAL_VAR = 11;
  const int INITIALIZED_CONST_LOCAL_VAR =  10;
  static int UNTNTIALIZED_CONST_LOCAL_VAR;
  int UNINITALIZED_LOCAL_VAR;
  return a+b;
}
static int INITALIZED_STATIC_GLOBAL_VAR = 11;
//static限定在本文件内 就是一个定义
static int UNTNTIALIZED_STATIC_GLOBAL_VAR;

const int INITALIZED_CONST_GLOBAL_VAR =  10;
static const int INITALIZED_STATIC_CONST_GLOBAL_VAR =  10;

int INITALIZED_GLOBAL_VAR= 3;
//这是声明不是定义表明另外文件有一个VAR
int UNINITALIZED_GLOBAL_VAR;
int main()
{
  int a = 1; 
  int b = 1;
  int ret = myadd(a,b);
  return 0;

}
