#include"heap.h"
#include<string.h>
#define Swap(a,b) do{ \
HeapType tmp ; tmp = a; a = b; b = tmp;}\
while(0)\

int MaxCmp(HeapType a, HeapType b )
{
  return a > b;
}
int MinCmp(HeapType a, HeapType b)
{
  return a < b;
}
void HeapInit(Heap* heap,Compare p_cmp)
{
  if( heap == NULL  || p_cmp == NULL)
    return ;
  heap->size = 0;
  heap->p_cmp= p_cmp;

}
void HeapDestroy(Heap* heap)
{
  if(heap == NULL)
    return;
  heap->size = 0;
  heap->p_cmp = NULL;
}
static void HeapSwim(Heap* heap)
{
  if( heap == NULL )
    return;
  int child = heap->size - 1;
  int parent = (child - 1) / 2;
  while( child > 0 )
  {
    if(!heap->p_cmp(heap->array[parent],heap->array[child]))
    {
        Swap( heap->array[child],heap->array[parent] );
        child = parent;
        parent = (child - 1) / 2;
    }
    else 
      break;
  }
}
static void HeapSink(Heap* heap)
{
  if(heap == NULL)
    return;
  int  parent = 0;
  int  child = parent*2 +1;
  while(child < heap->size)
  {
    //有右子树 而且右子树比左子树更符合交换规则
    if(child + 1 < heap->size && !heap->p_cmp(heap->array[child ], heap->array[child + 1]))
    {
      child ++;
    }
    if( !heap->p_cmp(heap->array[parent], heap->array[child]) )
    {
      Swap(heap->array[parent], heap->array[child]);
      parent = child;
      child = child * 2 + 1;
    }
    else 
    {
      break;
    }
  }
}
void HeapInsert(Heap* heap, HeapType value)
{
  if(heap == NULL)
    return;
  heap->array[heap->size++] = value;
  HeapSwim(heap);
}
HeapType HeapTop(Heap* heap)
{
  if( heap == NULL )
    return -1;
  if( heap->size == 0 )
  return -1;
  Swap(heap->array[heap->size - 1],heap->array[0]);
  HeapType ret = heap->array[heap->size - 1];
  heap->size--;
  HeapSink(heap);
  return ret;
}
void  HeapBuild(Heap* heap, HeapType* array, int length)
{
  heap->size = 0;
  if( heap == NULL || array == NULL )
    return;
  int i = 0;
  while(heap->size < length)
  {
    HeapInsert(heap, array[i++]);    
  }
}
void HeapSort(Heap* heap, HeapType* array, int length)
{
  if(heap == NULL || array ==0|| length < 0)
    return;
  HeapBuild(heap, array, length);
  while(heap->size > 0)
  {
    HeapTop(heap);
  }
  memcpy(array,heap->array,length*sizeof(array[0]));
}

