#include<stdio.h>
#define MAX_SIZE 100
typedef struct _maxPQ
{
    int array[MAX_SIZE];
    int size;
}MAXPQ;
void init_MAXPQ(MAXPQ* pq)
{
    pq->array[0] = 0;
    int size = 1;
}
void sink(MAXPQ* pq, int n, int tail)
{
    if( pq == NULL )
        return;
    while(2*n <= pq->size )
    {
        int k = 2*n;
        if( k < pq->size )
        {

          k = pq->array[n] = pq->array[k] > pq->array[k + 1] ? k :k++ ;
        }
        if( pq->array[n] < pq->array[k] )
        {
           int tmp = pq->array[n];
           pq->array[n] = pq->array[k];
           pq->array[k] = tmp;
        }
        n = k;
    }
}
void swim(MAXPQ* pq)
{
    if( pq == NULL || pq->size < 2)
        return;
}
void exch(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void MAXPQ_SORT(MAXPQ* pq)
{
    if(pq == NULL || pq->size < 2)
        return;
    int k = pq->size  / 2;
    while(k >=1 )
    {
        sink(pq,k--,pq->size);
    }
    int n = pq->size-1;
    while(n > 1)
    {
        exch(pq->array,pq->array+n);
        --n;
        sink(pq,1,n);
    }
}
MAXPQ pq;
int main()
{
    int i = 1;
    for( ; i < 5; i++ )
    {
        pq.array[i+1] = i;
    }
    MAXPQ_SORT(&pq);
}
