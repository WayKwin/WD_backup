// 结构体 回调函数 表明 是大堆小队
//
#pragma once
#include<stdio.h>
#define MAX_SIZE 100
typedef int HeapType;
typedef int (*Compare)(HeapType a, HeapType b);
typedef struct _heap{
    HeapType array[MAX_SIZE];
    int size;
    Compare p_cmp;
}Heap;
int MaxCmp(HeapType a, HeapType b );
int MinCmp(HeapType a, HeapType b);
void HeapInit(Heap* heap, Compare cmp );
void HeapDestroy(Heap* heap);
void HeapInsert(Heap* heap, HeapType value);
HeapType HeapTop(Heap* heap);
void HeapBuild(Heap* heap, HeapType* array, int length);
void HeapSort(Heap* heap, HeapType* array, int length);
