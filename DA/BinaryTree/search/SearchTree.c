#include"SearchTree.h"
#include<stdlib.h>

#if 1
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
  /*printf("InsertByLoop\n");*/
  _SearchTreeInsert_R(*root,key);
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
      free(root);
      root = NULL;
      return NULL;
    }
    // root 非叶子节点 而且左子树为空,和右子树中最小元素交换,后删除找到的节点
    else if(root->lchild == NULL && root->rchild != NULL)
    {
      SearchTreeNode* to_return = root->rchild;
      free(root);
      root = NULL;
      return to_return;
    }
    // root 非叶子节点,右子树为空,和左子树中最大元素交换,后删除找到的节
    else if(root->rchild == NULL && root->lchild != NULL)
    {
      SearchTreeNode* to_return = root->lchild;
      free(root);
      root = NULL;
      return to_return;
    }
    // root 非叶子节点, 左子树中最大值和右子树中最大值 二选一交换 后删除找到的节
    else if(root->lchild != NULL && root->rchild != NULL)
    {
      //采用赋值法
      //在左子树取最大值
      SearchTreeNode* max = root->lchild;
      SearchTreeNode* max_parent = root->lchild; 
      while(max->rchild)
      {
        max_parent = max;
        max = max->rchild;
      }
      root->key = max->key;
      //左子树是叶子节点
      if(max_parent == max)
      {
        free(max);
        max = NULL;
        root->lchild = NULL;
      }
      else 
      {
        //不用判断将左子树的最大值至为空
        free(max_parent->rchild);
        max_parent->rchild = NULL;
      }
      //采用改变节点法
      //麻烦 考虑的太多
      return root;
    }
  }
  return root;
}

void SearchTreeRemove(SearchTreeNode** proot, SearchTreeType to_delete)
{
   if(proot == NULL)
     return;
   if(*proot == NULL)
     return;
  SearchTreeNode* root = * proot;
  if(root->key > to_delete)
  {
    SearchTreeRemove(&(*proot)->lchild,to_delete);
  }
  else if(root->key < to_delete)
  {
    SearchTreeRemove(&(*proot)->rchild,to_delete);
  }
  else if( root->key == to_delete)
  {
    if(root->lchild == NULL && root->rchild == NULL)
    {
      *proot = NULL;
      free(root);
      root = NULL;
    }
    else if(root->lchild != NULL && root->rchild == NULL)
    {
      *proot = root->lchild;
      free(root);
      root = NULL;
      return;
    }
    else if(root->rchild != NULL && root->lchild == NULL)
    {
      // proot->lchild = proot->lchild->rchild
      *proot = root->rchild;
      //root = (old)proot -> lchild
      free(root);
      root = NULL;
      return;
    }
    else if(root->lchild   && root->rchild)
    {
      // 交换节点法 右子树中最小的一个
      SearchTreeNode* to_swap = root->rchild;
      SearchTreeNode* to_swap_parent = root->rchild;
      while(to_swap->lchild)
      {
        to_swap_parent = to_swap;
        to_swap = to_swap->lchild;
      }
      root->key = to_swap->key;
      //to_delete的右子树不是是叶子节点的情况
      if(to_swap != root->rchild)
      {
        to_swap_parent ->lchild = NULL;
      }
      free(to_swap);
      to_swap = NULL;
      return;
    }
  }
   
}
#endif
#if 1
void _SearchTreeInsert_ByLOOP_Version1(SearchTreeNode* root, SearchTreeType key)
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
#endif
void _SearchTreeInsert_ByLOOP_Version2(SearchTreeNode* root, SearchTreeType key)
{
  SearchTreeNode* pre_node = root;
  SearchTreeNode* node = root;
  for(node = root; node != NULL;  )
  {
    if(node->key > key)
    {
      pre_node = node;
      node = node->rchild;
    }
   else  if(node->key < key)
    {
      pre_node = node;
      node = node->lchild;
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
    if(pre_node->key < node->key)
    {
      pre_node->rchild = node;
    }
    else 
    {
      pre_node->lchild = node;
    }
  }
}
void _SearchTreeRemove_ByLoop(SearchTreeNode** proot,SearchTreeType key)
{
  if( proot == NULL  )
    return;
  if( *proot == NULL )
    return;
  SearchTreeNode* root = *proot;
  SearchTreeNode* pre_root = NULL;
  while(root)
  {
    if(root->key > key)
    {
      pre_root = root;
      root = root->lchild;
    }
    else if(root->key < key)
    {
      pre_root = root;
      root = root->rchild;
    }
    else if(root->key == key)
    {
      break;
    }
  }
    //没找到 
  if(root == NULL)
  {
    return;
  }
  // 如果是根节点
  if(root == *proot)
  {
    free(*proot);
    *proot = NULL;
    return;
  }
  //删除节点左右子树都为空
  if(root->lchild == NULL && root->rchild == NULL)
  {

    if(pre_root->key > root->key)
    {
      pre_root->lchild = NULL;
    }
    else 
    {
      pre_root->rchild = NULL;
    }
    free(root);
    root = NULL;
  }
  else if(root->lchild != NULL && root->rchild == NULL)
  {
    if(pre_root->key > root->key)
    {
      pre_root->lchild = root->lchild;
    }
    else 
    {
      pre_root->rchild = root->lchild;
    }
    free(root);
    root = NULL;
  }
  else if(root->rchild != NULL && root->lchild == NULL)
  {
    if(pre_root->key > root->key)
    {
      pre_root->lchild = root->rchild;
    }
    else 
    {
      pre_root->rchild = root->rchild;
    }
    free(root);
    root = NULL;
  }
  else if(root->rchild != NULL && root->lchild != NULL)
  {
    //在左子树中找最大的吧, 使用赋值法删除节点
    SearchTreeNode* max = root->lchild;
    SearchTreeNode* pre_max = NULL;
    while(max->rchild)
    {
      pre_max = max;
      max = max->rchild;
    }
    root->key = max->key;
    //左子树是根节点
    if(pre_max == NULL)
    {
     free(root->lchild);
     root->lchild = NULL;
    }
    else 
    {
      //左子树中最大的 ,不用比值
      free(pre_max->rchild);
      pre_max->rchild = NULL;
    }
  }
}

