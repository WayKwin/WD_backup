#include<stdio.h>
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
void MergeSortByLoop(int array[],int tmpArray[],int length)
{
  int gap = 1;
  for( ; gap < length;  gap *= 2)
  {
    int i = 0;
    for(; i < length; i += 2*gap)
    {
        //本来是7 此时 hi = 8
     
        int hi = i + 2*gap;
        if( hi > length )
        {
          hi = length;
        }
        int mid  = i + ( hi - i ) /2;

        printf(" [%d,%d) ",i,hi);
        printf("[mid: %d]",mid);
        Merge(array,tmpArray,i,mid ,hi);
        /*int j = 0;*/
        /*for(; j < length ; j++ )*/
        /*{*/
          /*printf(" %d", array[j]);*/
        /*}*/
        /*printf("\n");*/
          /*}*/
    }
    printf("\n");
  }
}
//    双指针(不看)
int main()
{
  int array[] = {8,9,1,4,2,3,5};
  const int length = sizeof(array) / sizeof(array[0]);
  int tmpArray[length];
  MergeSortByLoop(array,tmpArray,length);
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


