#include "heap.h"
#include<stddef.h>
#define HEAD  do{\
printf("=========%s=========",_FUNCTION__);\
}while(0);\

void testHeapInsert()
{
  Heap heap;
  HeapInit(&heap,MaxCmp);
  HeapType i = 1;
  while(i <= 5 )
  {
    HeapInsert(&heap, i);
    i++;
  }
  while(heap.size)
  {
    HeapType ret = HeapTop(&heap);
    printf("%d ",ret);
  }
  printf("\n");
}
void TestHeapSort()
{
  Heap heap;
  HeapInit(&heap,MaxCmp);
  HeapType array[] = {5,4,3,2,1};
  int length = sizeof(array)/sizeof(array[0]);
  HeapSort(&heap, array, length);
  int i = 0;
  for( ; i  < length ; i++ )
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}
int main()
{
  TestHeapSort();
}
