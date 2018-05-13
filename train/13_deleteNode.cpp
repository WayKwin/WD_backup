#include<iostream>
typedef struct Node{
  Node* p_next;
  int key;
}Node;
void DeleteNode(Node* root_t, Node* node)
{
  Node* root = root_t;
  if(root == NULL || node == NULL)
    return;
  if(node->p_next == NULL)
  {
    //遍历删除
    while(root->p_next != node)
    {
      root = root->p_next;
    }
    free(root->p_next);
    root->p_next = NULL;
  }
  int next_value = node->p_next->key;
  int tmp = next_value;
  next_value = node->key;
  node->key = tmp;
  Node* to_delete = node->p_next;
  node->p_next = to_delete->p_next;
  free(to_delete);
  to_delete = NULL;
}
