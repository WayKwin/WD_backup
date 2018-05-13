#include"SearchTree.h"
#include<stddef.h>
#define HEAD  do{\
printf("=========%s=========",_FUNCTION__);\
}while(0);\

void testSearchTreeInsert()
{
  SearchTreeNode* root = NULL;
  SearchTreeInsert(&root,'1');
  SearchTreeInsert(&root,'2');
  SearchTreeInsert(&root,'3');
  SearchTreeInsert(&root,'4');
  SearchTreeInsert(&root,'5');
  Inorder(root);
  printf("\n");
}
int main()
{
  testSearchTreeInsert();
  return 0;
}

