#include<stdio.h>
#include<stdlib.h>
void BubleSort(int array[],int tmpArray[])
{

}
void Merge(int array[],int tmpArray[],int lo, int mid, int hi)
{
  int i = lo;
  for( ; i < hi; i ++ )
  {
    tmpArray[i] = array[i];
  }
  i = lo;
  int start = lo;
  int j = mid ;
  // 归并[lo,hi]
  // [lo,mid]
  // (mid,hi]
  while(  i < mid || j < hi )
  {
    if( i >= mid  )
    {
      array[start++] =tmpArray[j++]; 
      continue;
    }
    else if( j >= hi  )
    {
      array[start++] =tmpArray[i++];
      continue;
    }
    if( tmpArray[i] <= tmpArray[j])
    {
      array[start++] =tmpArray[i++]; 
      continue;
    }
    else 
    {
      array[start++] =tmpArray[j++]; 
      continue;
    }
  }
}
void MergeSort(int array[],int tmpArray[],int lo,int hi)
{
  // 不对称边界 
  //  结束条件就是 [0,1)   lo 永远不可能 <= hi
  //  所以还是采用对称边界
  if(lo+1 == hi )
    return;
  int mid = lo + (hi - lo ) /2;
  MergeSort(array,tmpArray,lo,mid);
  MergeSort(array,tmpArray,mid,hi);
  printf(" [%d,%d) ",lo,hi);
  printf("[mid: %d]",mid);
  Merge(array,tmpArray,lo,mid,hi);
}
// 非递归
// gap  1  2   4   8
// [0,1)[1,2) [2,3)[3,4)  [4,5)[5,6) [6,7)[7,8)
//    [0,2)     [2,4)        [4,6)     [6,8)
//        [0,4)                   [4,8)
//                    [0,8)
// [0,1)[1,2) [2,3)[3,4)  [4,5)[5,6) [6,7)
//    [0,2)     [2,4)        [4,6)     [6,7)
//        [0,4)                   [4,7)
//                    [0,7)
//把所有奇数都 + 1 偶数来看待
/*void MergeSortByLoop(int array[],int tmpArray[],int length)*/
/*{*/
  /*int gap = 1;*/
  /*// 8  lo 0  hi  7  (hi > length hi = length) */
  /*//        mid 4*/
  /*//7    lo 0   hi 7*/
  /*//        mid 4*/
  /*for( ; gap <= length + 1  ;  gap *= 2)*/
  /*{*/
    /*int i = 0;*/
    /*for(; i < length  ; i += gap)*/
    /*{*/
        /*int hi = i + gap;*/
        /*//注意先算mid*/
        /*int mid  = i + ( hi - i ) /2 ;*/
        /*//后考虑越界*/
        /*if( hi > length )*/
        /*{*/
          /*hi = length;*/
        /*}*/
        /*printf(" [%d,%d) ",i,hi);*/
        /*printf("[mid: %d]",mid);*/
        /*Merge(array,tmpArray,i,mid ,hi);*/
        /*int j = 0;*/
        /*for(; j < length  ; j++ )*/
        /*{*/
          /*printf(" %d", array[j]);*/
        /*}*/
        /*printf("\n");*/
    /*}*/
    /*printf("\n");*/
  /*}*/
/*}*/
void MergeSortByLoop(int array[],size_t size)
{
  if(size <= 1)
  {
    return;
  }
  // [0 2) [2,4) [4,5)
  //    [0,4)
  //      [0, 7)
  int* tmp = (int*) malloc(sizeof(int)* size);
  size_t gap = 1;
  for(; gap < size; gap *= 2)
  {
    size_t i = 0;
    for(; i < size; i += 2*gap)
    {
      size_t beg = i;
      size_t mid = i + gap;
      size_t end = i + 2 * gap;
      if( mid > size )
      {
        mid = size;
      }
      if( end > size )
      {
        end = size;
      }
        Merge(array,tmp,beg,mid,end);
    }
  }
}
void swap(int *a ,int *b )
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
int parition(int array[],int lo,int hi)
{
  if( hi - lo <= 1)
  {
    return lo;
  }
  hi--;
  int *key = array+lo;
  while(lo < hi)
  {
    while( hi > lo && array[hi] >= *key )
    {
      hi --;
    }
    while( hi > lo && array[lo] <= *key )
    {
      lo ++;
    }
    swap(array+hi,array+lo);
  }
  swap(array+lo,key);
  return lo;
}
//挖坑法
int parition2(int array[],int beg,int end)
{
  if( beg + 1 == end )
  {
    return beg;
  }
  int left = beg;
  int right = end -1;
  //挖坑
  int key = array[right];
  while(left < right)
  {
    while(left < right &&  array[left] <= key)
    {
      ++left;
    }
    //每次都判断一下以防越界
    if(left < right)
    {
      //填坑然后挖坑
      array[right--]=  array[left];
    }
    while(left< right && array[right] >= key)
    {
      right --;
    }
    if( left < right )
    {
      array[left++] = array[right];
    }
  }
  array[left]= key;
  return left;
}

void _QuickSort(int array[],int lo,int hi)
{
  if(hi - lo <= 1)
    return;
  int j = parition2(array,lo,hi);
  /*printf("%d\n",j);*/
  _QuickSort(array,lo,j);
  _QuickSort(array,j + 1,hi);
}
void QuickSort(int array[],int length)
{
  if(array == NULL || length <= 1 )
    return;
  _QuickSort(array,0,length);
}

//    双指针(不看)
int main()
{
  /*int array[] = {1,4,8,9,2,3,5};*/
  int array[] = {1,4,8,9,2,3,5};
  /*int array[] = {9,8};*/
  const int length = sizeof(array) / sizeof(array[0]);
  /*int tmpArray[length];*/
  /*MergeSort(array,tmpArray,0,length);*/
  /*MergeSortByLoop(array,tmpArray,length);*/
  /*MergeSortByLoop(array,length);*/
  QuickSort(array,length);
  int i = 0;
  for(; i < length ; i++ )
  {
    printf(" %d", array[i]);
  }
  printf("\n");
}
/** 
 * @brief
 *  平均 o(n*logn) 最坏(on^2) 逆序
 * 空间 o(n) 递归 n次   1  3 4 5 6   
 * @param array[]
 * @param size   
 */
void QuickSortByLoop(int array[],size_t size)
{
  if(size <= 1)
  {

  }
  //Push beg
  //push end
  while(1)
  {
    // if top  == 0
    // return
    // if( end - beg <= 1 )
    // {
    //    //已经有序了, continue;
    // }
    // [lo,mid) 和 [mid + 1, hi)
    // Push beg
    // push mid
    // push mid +1
    // push end
  }
}
// 改进方法
//  1 选取基准值: 三个元素取中间值
//  2 当递归深度达到一定值时,不再继续递归,把排序改进为堆排序
//  3 递归到一定程度,子区间的元素很小,改成插入排序
///////////////////////////////////////////////////////////
// 计数排序
/////////////////////////////////////////////////////////
//下标年龄 内容出现次数
////////////////////////////
//基数排序
///////////////////////////
// 睡眠排序
//线程 睡眠 时间
////////////////////
//猴子排序
/////////////////////


