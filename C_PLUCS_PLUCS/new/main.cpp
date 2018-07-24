#include<iostream>

void* operator new(size_t size)
{
  printf("operator new called\n");
  return  NULL;
}
int main()
{
  int *a = new int[10];
  return 0;
}
