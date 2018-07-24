#include<stdio.h>
int  memmove(void* dst,void*src,size_t size)
{
  if(dst == NULL || src == NULL)
    return -1;
  
  // void* 不能进行+=
  char* d = (char*) dst;
  char* s = (char*) src;
  size_t length = size;
  if( d == s )
    return 0;
  if(s+ size > d)
    while(length--)
      *(s+length) = *(d + length);
  else // (d + length > s )
  {
    length = 0;
    while(length < size)
    {
        *(s+length) = *d;
        length++;
    }
  }
  return 0;
}
