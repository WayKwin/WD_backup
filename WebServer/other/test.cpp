#include<stdio.h>
#include<list>
#include<string.h>
#include<unistd.h>
#include<strings.h>
#include<stdarg.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<assert.h>
using namespace::std;
//what fuck
//template<typename T> void test(T a)
//{
  //list<T> b;
  //b.push_back(a);
  //cout<< b.front() << endl;
//}
//struct events 
//{
  //static int a;
  //void process()
  //{
    //a++; 
    //printf(" doing somethings,%d\n",a);
  //}
//};
//int events::a= 0;
//void test_threadpool()
//{
  //events a;
  //ThreadPool<events>* tp = new ThreadPool<events>;
  //printf(" main thread waiting \n");
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
  //tp->SetEvents(&a);
//}
void test_strpbrk()
{
  char text[1024] = "GET /usr/lcoal.jpg http/1.1";

  // 坑: strtok虽然方便, 但是内部用了静态变量,不适合多线程版
  // bug strtok_r 是线程安全版本的

  //char* method =  strtok(text," ");
  //char* url =  strtok(NULL," ");
  //char* version =  strtok(NULL," ");

  char* method = text;
  char* cur = strpbrk(text," \t");
  *cur++ = '\0';

  char* url = cur;
  cur = strpbrk(url," \t");
  *cur++ = '\0';

  char* version = cur;
  if(strcasecmp(version,"HTTP/1.1") != 0)
    printf("not http/1.1\n");
  //cur = strpbrk(url," \t");
  //*cur++ = '\0';
  printf("%s\n",method);
  printf("%s\n",url);
  printf("%s\n",version);
  
}
int mon_log(char* format,...)
{
  char str_tmp[50];
  int i = 0;
  va_list vArgList;
  va_start(vArgList,format);
  i = vsnprintf(str_tmp,50,format,vArgList);
  va_end(vArgList);
  printf("%s",str_tmp);
  return i;
}
void test_vsnprintf()
{
  int i = mon_log((char*)"%s,%d,%d,%d","asd",2,3,4);
  printf("%d\n",i);
}
//void test_env()
//{
  ////putenv("hello");
  //setenv("hello","world",0);
  //int pid = fork();
  //if(pid  == 0)
  //{
    //printf("%s\n",getenv("hello"));
  //}
  //else 
  //{
    //printf("%s\n",getenv("hello"));
  //}
//}
void test_socketpairt()
{
  int sockfd[2]; 
  int ret = socketpair(AF_LOCAL,SOCK_STREAM,0,sockfd);
  assert(ret >= 0);
  //dup2(sockfd[0],fileno(stdin));
  //dup2(sockfd[1],fileno(stdout));
  int pid  = fork();
  assert(pid >= 0);
  if(pid == 0)
  {
    close(sockfd[0]);
    //dup2(fileno(stdout),sockfd[1]);
    dup2(sockfd[1],fileno(stdout));
    //printf("%d\n",sockfd[1]);
    char* file = "./cgi";
    char* argv[] = {file,NULL};
    if(execvp(file,argv) < 0)
    {
      printf("execv error \n");
    }
  }
  else if(pid > 0)
  {
    close(sockfd[1]);
    char recvbuf[2048];
    int ret = recv(sockfd[0],recvbuf,sizeof(recvbuf),0);
    if(ret < 0)
    {
      printf("erorr\n");
      return ;
    }
    if(ret == 0)
    {
      printf("close \n");
    }
      printf(" in father:%s",recvbuf);
  }
}
int main()
{
  test_socketpairt();
  //test_env();
  //test_strpbrk();
  //test_threadpool();
  return 0;
}
