#include"BinaryTree.h"
static int _FindNodeLeft(treeNode* root,treeNode* node)
{
  //double check
  if( root == NULL || node == NULL )
    return 0;
  if( root == node )
    return 1;
  int to_find = _FindNodeLeft(root->left, node);
  return to_find;
}
static int _FindNodeRight(treeNode* root,treeNode* node)
{
  if( root == NULL || node == NULL )
    return 0;
  if( root == node )
    return 1;
  int to_find = _FindNodeRight(root->right, node);
  return to_find;
}

//如果分别在左子树和右子树中找到了node1和node2, 公共祖先在root
//如果在右面没有照东啊node1和node2,最近公共祖先就是左子树
//递归
static treeNode* _LastCommonFather(treeNode*root, treeNode* node1,treeNode*node2)
{
  int LeftReach = _FindNodeLeft(root, node1);
  int RightReach = _FindNodeRight(root,node2);
  if( LeftReach && RightReach )
  {
    return root;
  }
  //doublecheck
  if( !LeftReach && !RightReach )
  {
    return NULL;
  }

//根节点左边没找到就在右边找
  return  LeftReach == 1? _LastCommonFather(root->left, node1, node2): _LastCommonFather(root->right, node1,node2);
}
treeNode* LastCommonFather(treeNode*root, treeNode* node1,treeNode*node2)
{
  if( node1 == NULL || node2 == NULL || root == NULL || node1 == root || node2 == root )
    return NULL;
  //判断node1 和node2 在左子树还是右子 
  return _LastCommonFather(root,node1,node2);
}
