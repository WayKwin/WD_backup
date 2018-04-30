#include<stdio.h>
#define Swap(a,b) int tmp = a; a = b; b = tmp
int Partition(int data[], int start, int end)
{
    if(start >= end )
    {
        return start;
    }
    int base = data[start];
    //考虑 3 4 5 的情况  head必须从切分点开始
    /*int head_point = start + 1;*/
    int head_point = start;
    int tail_point = end ;
    while(head_point < tail_point)
    {
        while(head_point < tail_point && data[tail_point] >= base)
        {
            tail_point--;
        }
        while(head_point < tail_point && data[head_point] <= base)
        {
            head_point++;
        }
        Swap(data[head_point], data[tail_point]);
    }
    int j = head_point;
    Swap(data[head_point], data[start]);
    return j;
}
void QuickSort(int data[], int head,int tail)
{
    if( head >= tail )
        return;
    int j = Partition(data, head, tail);
    printf("%d\n", j );
    QuickSort(data, head , j - 1);
    QuickSort(data,  j + 1 ,tail);

}
int main()
{
    int i;
    int data[] = { 2, 4, 3, 5, 1 };
    QuickSort(data,  0, 4);

    /*Partition(data,0,4);*/
    for(i = 0; i < 5; i++)
    {
        printf("%d ",data[i]);
    }
    printf("\n");
}
