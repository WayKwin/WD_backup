#pragma once
#include<stdlib.h>
#include<stddef.h>
#define SeqListInitCapacity 30
#define SeqListtype int
#define CheckNULL if(a==NULL)return
#define OutofCapacity (size>capacity?1:0)
#define CheckSize if(size<=0)return

class SeqList{
private:
	int *a;
	SeqListtype size;
	SeqListtype capacity;
public:
	void SeqListInit();
	SeqList(){ SeqListInit(); }
	~SeqList(){  }
	void PushBack(int value);
	int PopBack();
	void showSeqList();
	void PushFront(int value);
	int PopFront();
	void insert(int key, int value);
	int remove(int key);
	int IncreaseCapacity();
};
