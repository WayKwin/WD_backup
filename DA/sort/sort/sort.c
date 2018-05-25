
/** 
 * @brief
 * 
 * @param array[]
 * @param size   
 * 
 * @return 
 * 冒泡
 */
#include<stdio.h>
void Swap(int *a, int * b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void BubbleSort(int array[], size_t size)
{
  size_t bound = 0;
  size_t j = 0;
  for(; bound < size - 1; ++bound){
  for(j = 0; j < size - 1 - bound; j ++  )
  {
    if(array[j] > array[j + 1] ) 
    {
      Swap(array + j, array + j + 1);
    }
  }
  }
}
/** 
 * @brief
 */
void Insertion(int array[], size_t size)
{
  size_t bound = 0;
  int  cur;
  size_t Save_value ;
  for( ; bound < size; bound ++ )
  {
    Save_value = array[bound];
   for( cur = bound ; cur > 0 ; cur --  )
   {
    if( array[cur] < array[cur-1]  )
    {
      array[cur] = array[cur - 1];
    }
    else 
    {
      // 1 0 
      // cur = 0
      // 
     array[cur] = Save_value; 
    }
   }
  }
}
/**
 *堆排序 
 * 
*/
void sink(int array[],size_t size,size_t i)
{
    while( 2 * i + 1 < size )
    {
      int child = 2 * i + 1;
      if( 2 * i + 2 < size &&  array[2*i + 1] < array[2*i + 2] )
      {
        child += 1;
      }
      if(array[i] < array[child])
      {
        Swap(array + i, array + child);
        i = child;
      }
      else break;
  }
}
void HashPop(int array[],size_t heap_size)
{
  //将堆顶元素和末尾元素置换,
  //然后恢复堆的有序性
  Swap(array , array +  heap_size - 1);
  sink(array, heap_size - 1, 0);   
}
void HeapCreate(int array[],size_t size)
{
   // size_t 不能 判断 i >=0  --i    死循环
  int i = size - 1 -1 / 2;
  while(i > 0)
  {
    sink(array,size,i);
    i--;
  }
}
void HeapSort(int array[],size_t size){
  HeapCreate(array,size);
  size_t heap_size = size;
  while(heap_size > 0)
  {
    HashPop(array,heap_size);
    heap_size--;
  }
}
/*int main()*/
/*{*/
  /*int array[] = { 5,4,3,2,1 };*/
  /*int length = sizeof(array) / sizeof(array[0]);*/
  /*HeapSort(array,length);*/
  /*int i  =0;*/
  /*for(; i < length; i++)*/
  /*{*/
    /*printf(" %d", array[i]);*/
  /*}*/
  /*printf("\n");*/
/*}*/

/*
 * 
 *希尔排序 希尔序列  N/2  N/4 N/8 tg, 
 * 
 */
/*void ShellSort(int array[],int size)*/
/*{*/

/*}*/
