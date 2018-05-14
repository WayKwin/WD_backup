#include"SearchTree.h"
#include<stdlib.h>
#if 0
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
  //为空 插入新元素
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
SearchTreeNode* _SearchTreeRemove(SearchTreeNode* root, SearchTreeType to_delete)
{
  //  proot = * root //二级指针
  //将 &(root->left) 传入递归函数中
   //  * 就是父节点
  if(root == NULL)
    return NULL;
  if(root->key > to_delete)
  {
    root->lchild = _SearchTreeRemove(root->lchild,to_delete);  
  }
  if(root->key < to_delete)
  {
    root->rchild = _SearchTreeRemove(root->rchild,to_delete);
  }
  if(root->key == to_delete)
  {
    // root 是叶子节点
    if(root->lchild == NULL && root->rchild == NULL)
    {

    }
    // root 非叶子节点 而且左子树为空,和右子树中最小元素交换,后删除找到的节点
    else if(root->lchild == NULL && root->rchild != NULL)
    {

    }
    // root 非叶子节点,右子树为空,和左子树中最大元素交换,后删除找到的节
    else if(root->rchild == NULL && root->lchild)
    {

    }
    // root 非叶子节点, 左子树中最大值和右子树中最大值 二选一交换 后删除找到的节
    else if(root->lchild != NULL && root->rchild != NULL)
    {

    }
    
  }
  return root;
}
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType to_delete)
{
   if(root == NULL)
     return;
  SearchTreeNode* proot = * root;
  SearchTreeRemove(&(*root)->lchild,to_delete);
  //递归
  proot = NULL;
   
}

#endif
//
void SearchTreeInit(SearchTreeNode** root,SearchTreeType key)
{
// 通过大小判断左右子树
}
void SearchTreeRemove(SearchTreeNode** proot, SearchTreeType to_delete)
{
  //先找到要删除的节点
  SearchTreeNode* to_remove_node = *proot;
  SearchTreeNode* parent = *proot;
  //找元素
  


  // 分情况讨论
  // 叶子节点
  // 单子树
  // 双子树
  // 删除的是根节点 parent有可能是空单独考虑
}



