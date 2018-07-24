#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>
using namespace std;
class A
{
  public:
  int a;
  string b;
  A():a(10),b("123"){};
};
int ss()
{
  char a[] ="123";
  char b[] ="456";
  char c[] ="789";
  char *src[] = {a,b,c};
  char *dst[] = {"abc","def","ghi"};
  memmove(dst,src,sizeof(src));
  //char* tmp = dst[0];

  //dst[0] =  dst[1];

  //dst[1] = tmp;
  return 0;
}
int main()
{
  A*src = new A[10];
  A *dst = new A[10];
  memcpy(dst,src,sizeof(A)*10);
  
  //cout <<dst[0] << endl;
  //cout <<src[0] << endl;

  
  


  dst[1].b ="346";
  dst[1].a=1;
  //printf("src[1].b: %s\n",src[1].b.c_str());
  cout << src[1].b << endl;
  //printf("dst[1].b: %s\n",dst[1].b.c_str());
  //cout << src[1].b<<endl;
  //cout << src[1].a<<endl;




}
