#include"SearchTree.h"
#include<stddef.h>
#define HEAD  do{\
printf("\n=========%s=========\n",__FUNCTION__);\
}while(0);\

void testSearchTreeInsert()
{
  SearchTreeNode* root = NULL;
  SearchTreeInsert(&root,'5');
  SearchTreeInsert(&root,'3');
  SearchTreeInsert(&root,'1');
  SearchTreeInsert(&root,'2');
  SearchTreeInsert(&root,'4');
  Inorder(root);
  printf("\n");
}
void testSearchTreeRemove()
{
  HEAD;
  SearchTreeNode* root = NULL;
  SearchTreeInsert(&root,'5');
  SearchTreeInsert(&root,'3');
  SearchTreeInsert(&root,'1');
  SearchTreeInsert(&root,'2');
  SearchTreeInsert(&root,'4');
  Inorder(root);
  printf("\n");
  SearchTreeRemove(&root, '3');
  Inorder(root);
  printf("\n");
  _SearchTreeRemove_ByLoop(&root, '2');
  Inorder(root);
  printf("\n");
}

int main()
{
  testSearchTreeRemove();
  return 0;
}

