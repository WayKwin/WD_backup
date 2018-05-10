// 结构体 回调函数 表明 是大堆小队
//
#define MAX_SIZE 100
typedef int (*Compare)(HEAP_TYPE a, HEAP_TYPE b) Cmopare;
typedef int HEAP_TYPE;
typedef struct _heap{
    HEAP_TYPE array[MAX_SIZE];
    int size;
    Cmopare;
}
void HeapInit(Heap* heap, Compare cmp );
void HeapDestroy(Heap* heap);
void HeapInset(Heap* heap, HeapType value);
int HeapRoot(Heap* heap,HeapType* value);

