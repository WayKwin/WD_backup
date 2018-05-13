#include"SearchTree.h"
#include<stdlib.h>
void SearchTreeInit(SearchTreeNode** root,SearchTreeType key)
{
  if(root == NULL)
    return;
  if(*root == NULL)
  {
    *root = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
  }
  SearchTreeNode* node = *root;
  node->rchild = NULL;
  node->lchild = NULL;
  node->key = key;
}
SearchTreeNode* _SearchTreeInsert_R(SearchTreeNode* root, SearchTreeType key)
{
  if(root == NULL)
  {
    root = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
    root->key = key;
    root->rchild = NULL;
    root->rchild = NULL;
  }
  if(key > root->key)
  {
    root->rchild = _SearchTreeInsert_R(root->rchild,key);
  }
  else if(key < root->key)
  {
    root->lchild = _SearchTreeInsert_R(root->lchild,key);
  }
  else if( key == root->key )
  {
    return root;
  }
  return root;
}
void _SearchTreeInsert_L(SearchTreeNode* root, SearchTreeType key)
{
  SearchTreeNode* pre_node = root;
  SearchTreeNode* node = root;
  int LastFlag = 0;
  for(node = root; node != NULL;  )
  {
    if(node->key > key)
    {
      pre_node = node;
      node = node->rchild;
      if(node == NULL)
      {
        LastFlag = 1;
      }
    }
   else  if(node->key < key)
    {
      pre_node = node;
      node = node->lchild;
      if(node == NULL)
      {
        LastFlag = 0;
      }
    }
   else if(node->key == key)
   {
     break;
   }
  }
  if(node == NULL)
  {
    node  = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
    node->key = key;
    node->lchild = NULL;
    node->rchild = NULL;
    if(LastFlag)
    {
      pre_node->rchild = node;
    }
    else 
    {
      pre_node->lchild = node;
    }
  }
}
void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key)
{
  if(root == NULL)
    return;
  if(*root == NULL)
  {
    SearchTreeInit(root,key);
  }
  printf("InsertByLoop\n");
  _SearchTreeInsert_L(*root,key);
}
void Inorder(SearchTreeNode* root)
{
  if(root == NULL)
    return;
  printf("%c ", root->key);
  Inorder(root->lchild);
  Inorder(root->rchild);
}
