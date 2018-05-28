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
 *  * @brief
 *   */
void Insertion(int array[], size_t size)
{
    size_t bound = 0;
    int  cur;
    int  Save_value ;
    for( ; bound < size; bound ++  )
    {
      Save_value = array[bound];
         for( cur = bound - 1 ; cur >= 0 ; cur -=1   )
         {
           if(array[cur]  > Save_value)
           {
               array[cur + 1] = array[cur];
           }
           else 
             break;
         }
         array[cur] = Save_value;
    }
}
void shellSort(int array[],size_t size)
{
  int gap = size / 2;
  int i = 0;
  int j = 0;
  for(; gap > 1; gap /= 2 )
  {
    for( i = 0; i < size; i++ )
    {
      for( j = i; j  )
    }
  }
}
/**
 *  *堆排序 
 *   * 
 *   */
void sink(int array[],size_t size,size_t i)
{
      while( 2 * i + 1 < size  )
      {
              int child = 2 * i + 1;
                    if( 2 * i + 2 < size &&  array[2*i + 1] < array[2*i + 2]  )
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
    //  //然后恢复堆的有序性
    //    Swap(array , array +  heap_size - 1);
    //      sink(array, heap_size - 1, 0);   
    //
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
                              }
                      }
            }
}
