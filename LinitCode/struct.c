#include<stdio.h>

typedef struct a{
  struct{int x,y,z;} u;
  int k ;
}a;
int main()
{
  a a;
  a.u.y = 5; a.u.z = 6;
  printf("%d\n",a.u.y);
  return 0;
}
