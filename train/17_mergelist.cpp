#include<iostream>
#include<stdlib.h>
using namespace ::std;
typedef struct Node{
  Node* p_next;
  int key;
}Node;
Node* mergeList(Node* node1,Node* node2)
{
  if( node1 == NULL || node2 == NULL )
  {
    return node1 == NULL? node2 : node1;
  }

  Node* new_head = (Node*)malloc(sizeof(Node));
  Node* ret = new_head ;
  Node* tmp = new_head;
  new_head->p_next = NULL;
  Node* cur1 = node1;
  Node* cur2 = node2;
  // 使用continue 而不是else if
  while(1)
  {
    if(cur1 == NULL && cur2 == NULL)
      break;
    else if(cur1 != NULL && cur2 == NULL)
    {
      new_head->key = cur1->key;
      Node* to_delete = cur1;
      cur1 = cur1->p_next;
      //free(to_delete);
      //to_delete = NULL;
    }
    else if(cur1 == NULL && cur2 != NULL)
    {
      new_head->key = cur2->key;
      Node* to_delete = cur2;
      cur2 = cur2->p_next;
      //free(to_delete);
      //to_delete = NULL;
    }
    else if(cur1->key >= cur2->key)
    {
      new_head->key = cur2->key;
      Node* to_delete = cur2;
      cur2 = cur2->p_next;
      //free(to_delete);
      //to_delete = NULL;
    }
    else if(cur1->key < cur2->key)
    {
      new_head->key = cur1->key;
      Node* to_delete = cur1;
      cur1 = cur1->p_next;
      //free(to_delete);
      //to_delete = NULL;
    }
    if( cur1 == NULL && cur2 == NULL )
    {
      break;
    }
    new_head->p_next = (Node*) malloc(sizeof(Node)); 
    new_head = new_head->p_next;
  }
  // 前一个元素的p_next没有释放
  return ret;
}
int main()
{
  Node head ;
  head.key = 1;
  Node node2 ;
  node2.key = 3;
  Node node3 ;
  node3.key = 5;
  head.p_next = &node2;
  node2.p_next = &node3;
  node3.p_next = NULL;
  
  Node head2;
  head2.key = 2;
  Node node22;
  node22.key = 4;
  Node node33;
  node33.key = 6;
  head2.p_next = &node22;
  node22.p_next = &node33;
  node33.p_next = NULL;
  Node* new_head = mergeList(&head, &head2);
  while(new_head != NULL)
  {
    cout << new_head->key << " ";
    new_head = new_head->p_next;
  }
  return 0;
}

