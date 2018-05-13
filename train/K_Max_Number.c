#include<stdio.h>
int partition(int* array, int lo, int hi)
{
    if( array == NULL || lo <0 ||  hi < lo  )
        return -1;
    if( lo >= hi )
    {
        return lo;
    }
    int key = array[lo];
    while( lo < hi )
    {
        while(  lo < hi && array[hi] >= key )
        {
            hi--;
        }
        while( lo < hi && array[lo] <= key )
        {
            lo++;
        }
        int temp = array[lo];
        array[lo] = array[hi];
        array[hi] = temp;
    }
    int temp = array[lo];
    array[lo] = key;
    key = temp;
    return lo;
}
int partition_Max(int* array, int lo, int hi)
{
  if(array == NULL || lo >= hi || lo < 0)
  {
    return -1;
  }
  int key = array[lo];
  while( lo < hi )
  {
    while( lo < hi && array[hi] < key )
    {
      hi--;
    }
    while( lo < hi && array[lo] > key )
    {
      lo++;
    }
    int temp = array[lo];
    array[lo] = array[hi];
    array[hi] = temp;
  }
    int temp = array[lo];
    array[lo] = key;
    key = temp;
    return lo;
    
}
int max_k_number_max(int* array, int length, int rank)
{
    if( array == NULL || length <=0 )
    {
        return -1;
    }
    int lo = 0;
    int hi = length - 1;
    int k = partition_Max(array,lo, hi);
    //注意 k返回的是下标
    //得让k++
    k++; 
    while( k != rank )
    {
      //找大了
      if( k < rank )
      {
         k = partition_Max(array, k + 1, hi);
      }
      // 找小了
      else if( k > rank )
      {
        k = partition_Max(array, lo, k - 1);
      }
      k++;
    }
    // 结束的时候还要 - 1 返回下标形式//还是下面方法简单
    return array[k - 1];
}
int max_k_number(int* array,int length, int rank)
{
    if( array == NULL || length <=0 )
    {
        return -1;
    }
    int lo = 0;
    int hi = length - 1;
    int k = partition(array,lo, hi);
    int max = length - k;
    while(  max  != rank  )
    {
        //第几大元素
         //1    3
        if (max  < rank)
        {
          k = partition(array,  lo, k - 1 );
        }
        else if ( max > rank )
        {
            k = partition(array,  k + 1, hi );
        }
         max = length - k;
    }
    return array[k];
}
int main()
{
    int array[] = {5, 8, 3, 2};
    int length = sizeof(array)/sizeof(array[0]);
    int ret = max_k_number_max(array,length, 1);
    printf("%d ", ret);
}
