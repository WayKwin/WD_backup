#include<iostream>
#include<stddef.h>
#include<stdio.h>
#include"SeqList.h"
#define p printf("\n=========%s==========\n",__FUNCTION__)
SeqList s;
void testPushBack()
{
	p;
	s.PopBack();
	s.PushBack(1);
	s.PushBack(2);
	s.PopBack();
	s.showSeqList();
}
void testFront()
{
	p;
	s.PopFront();
	s.PushFront(3);
	s.PushFront(2);
	s.PushFront(1);
	s.PopFront();
	s.showSeqList();
}
void testInsert_Remove()
{
	p;
	s.insert(0,1);
	s.insert(1,2);
    s.insert(2,3);
    s.remove(0);
	s.showSeqList();
}
int main()
{
	testInsert_Remove();
	return 0;
}
