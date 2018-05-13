#include<iostream>
using namespace ::std;
typedef struct Node{
  Node* p_next;
  int key;
}Node;
Node* FindKthTotail(Node* phead,size_t k)
{
  if( phead == NULL || k == 0 )
  {
    return NULL;
  }
  Node* frist = phead;
  //考虑溢出
  size_t frist_step = k - 1;
  while(frist != NULL &&frist_step--){
     frist = frist->p_next; 
  }
  if(frist == NULL)
  {
    return  NULL;
  }
  Node* after = phead;
  //当走到最后一个节点
  // 3
  // 倒数第一个节点
  // 
  while(frist->p_next)
  {
    after = after->p_next;
  }
  return after;
}
int main()
{
  Node head ;
  head.key = 1;
  Node node2 ;
  node2.key = 2;
  Node node3 ;
  node3.key = 2;
  head.p_next = &node2;
  node2.p_next = &node3;
  node3.p_next = NULL;
  Node* ret = FindKthTotail(&head,3);
  cout<< ret->key << endl;
  return 0;
  

}

