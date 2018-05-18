#include<iostream>
using namespace::std;
struct ComplexListNode
{
  int m_nValue;
  ComplexListNode* m_pNext;
  ComplexListNode* m_pSibling;
};
void CopyList(ComplexListNode* head)
{
  if(head == NULL)
    return;
  ComplexListNode* cur = head;
  ComplexListNode*tmp = cur;
  while(cur != NULL)
  {
    ComplexListNode* new_node = (ComplexListNode*)malloc(sizeof(ComplexListNode));
    new_node->m_nValue =cur->m_nValue;
    tmp = cur->m_pNext;
    new_node->m_pNext =cur->m_pNext;
    cur->m_pNext = new_node;
    cur = tmp;
  }
  while(head)
  {
    cout << head->m_nValue << " ";
    head = head->m_pNext;
  }
  cout<< "over"<<endl;

}
void CopyComplexNode(ComplexListNode* head)
{
  if(head == NULL)
    return;
  ComplexListNode* cur = head;
  while(cur->m_pNext->m_pNext)
  {
    if(cur->m_pSibling == NULL)
    {
      cur->m_pNext->m_pSibling = NULL;
      //counitnue之前让指针能移动
      cur = cur->m_pNext->m_pNext;
      continue;
    }
    cur->m_pNext->m_pSibling = cur->m_pSibling->m_pNext;
    cur = cur->m_pNext->m_pNext;
  }
}
ComplexListNode*  ComplexListNodeDetach(ComplexListNode* head)
{
  if(head == NULL)
    return NULL;
  ComplexListNode* cur = head;
  ComplexListNode* head2 = head->m_pNext;
  //偶数不会越界
  while(cur->m_pNext->m_pNext)
  {
    cur->m_pNext = cur->m_pNext->m_pNext;
    head2->m_pNext = head2->m_pNext->m_pNext;
    cur = cur->m_pNext->m_pNext;
  }
  return head2;
}
ComplexListNode* ComplexListNodeCopy(ComplexListNode* head)
{
  if(head == NULL)
  return NULL;
  CopyList(head);
  CopyComplexNode(head);
  cout<< "over"<<endl;
  ComplexListNode* Node  = ComplexListNodeDetach(head);
  return Node; 
}
int main()
{
  ComplexListNode* Node1 = (ComplexListNode*)malloc(sizeof(ComplexListNode));
  Node1->m_nValue = 1;
  ComplexListNode* Node2 = (ComplexListNode*)malloc(sizeof(ComplexListNode));
  ComplexListNode* Node3 = (ComplexListNode*)malloc(sizeof(ComplexListNode));
  ComplexListNode* Node4 = (ComplexListNode*)malloc(sizeof(ComplexListNode));
  Node2->m_nValue = 2;
  Node3->m_nValue = 3;
  Node4->m_nValue = 4;
  Node1->m_pNext = Node2;
  Node2->m_pNext = Node3;
  Node3->m_pNext = Node4;
  Node4->m_pNext = NULL;
  Node1->m_pSibling = Node2;
  Node2->m_pSibling = NULL;
  Node3->m_pSibling  = Node1;
  Node4->m_pSibling = Node4;
 ComplexListNode* ret = ComplexListNodeCopy(Node1); 
 while(ret)
 {
   cout<< ret->m_nValue;
   if(ret->m_pSibling == NULL)
   {
      cout<<"NULL";
      ret = ret->m_pNext;
      continue;
   }
   cout<< ret->m_pSibling->m_nValue;
   ret = ret->m_pNext;
 }
}
