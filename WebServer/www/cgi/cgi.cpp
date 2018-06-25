#include<stdio.h>
#include<stdlib.h>
int main()
{
  char * url = getenv("QUERY_STRING");
  if(url != NULL)
  {
    printf("i got url %s",url);
  }
  char * method = getenv("METHOD");
  if(method != NULL)
  {
    printf("i got method %s ",method);
  }
  return 0;
}
