#include<iostream>
using namespace ::std;
typedef struct Node{
  Node* p_next;
  int key;
}Node;
void  ReverseList(Node* root)
{
  if(root == NULL)
    return ;
  Node* cur = root;
  Node* preNode = NULL;
  Node* tmp = NULL;
  while(cur)
  {
    tmp = cur; 
    cur = cur->p_next;
    tmp->p_next = preNode;
    preNode = tmp;
  }
}
int main()
{
  Node head ;
  head.key = 1;
  Node node2 ;
  node2.key = 2;
  Node node3 ;
  node3.key = 3;
  head.p_next = &node2;
  node2.p_next = &node3;
  node3.p_next = NULL;
  ReverseList(&head);
  Node* root = &node3;
  while(root)
  {
    cout<<root->key <<endl;
    root = root->p_next;
  }
  return 0;
}
