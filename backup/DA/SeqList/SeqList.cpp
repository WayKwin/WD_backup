#include"SeqList.h"
#include<iostream>
void SeqList::SeqListInit()
{
	a = (int *)malloc(sizeof(int)*SeqListInitCapacity);
	if (a == NULL)
	{
		return;
	}
	size = 0;
}

int  SeqList::IncreaseCapacity()
{
	return 0;
}
void SeqList::PushBack(int value)
{
	CheckNULL;
	if (OutofCapacity)
		IncreaseCapacity();
	a[size++] = value;
}
int SeqList::PopBack()
{
	CheckNULL -1;
	CheckSize  -1;
	return a[--size];
}
void SeqList::PushFront(int value)
{
	CheckNULL;
	if (OutofCapacity)
		IncreaseCapacity();
	size++;
	for (int i = size - 1; i >0; i--)
	{
		a[i] = a[i-1];
	}
	a[0] = value;
}
int SeqList::PopFront()
{
	CheckNULL - 1;
	CheckSize - 1;
	for (int i = 0; i < size - 1; i++)
	{
		a[i] = a[i + 1];
	}
	size--;
}
void SeqList::insert(int key,int value)
{
	CheckNULL;
	if(key>size) return ;
	size++;
	for(int i = size - 1; i - 1>= key; i --)
	{
		a[i]=a[i - 1];
	}
	a[key]=value;
}
int SeqList::remove(int key)
{
	CheckNULL -1;
	CheckSize -1;
	if(key > size - 1) return -1;
	int ret=a[key];
	for(int i = key; i + 1 < size; i++)
	{
		a[i] = a[i + 1];
	}
	size--;
	return ret;
}
int SeqList::IncreaseCapacity()
{
    int *tmp=(int *)realloc(a,);
    for(int i = 0; i < size;i ++)
    {

    }
}
void SeqList::showSeqList()
{
	CheckNULL;
	CheckSize;
	for (int i = 0; i < size; i++)
	{
		std::cout << a[i];
	}
	std::cout<<std::endl;
}
