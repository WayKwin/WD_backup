#include"shell.h"
void merge(int *array1,int size, int *array2, int size)
{

}
int mergeSort(int *array,int size)
{
    int i = 0;
    int mid = i + ( size-i ) / 2;
    if (mid == 0 || mid == size)
        return;
    merge(array, mid,array+1, mid);
    merage(0,mid);
    merage(mid+1,size-1);

}
