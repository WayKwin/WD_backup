#include<iostream>
struct BinaryTreeNode
{
  int m_nValue;
  BinaryTreeNode* m_pLeft;
  BinaryTreeNode* m_pReft;
};
//转换根节点 将根节点和左子树中最大和右子树中最小连接起来
//在左子树中也将最小和最大连接起来
//递归
BinaryTreeNode* FindMax(BinaryTreeNode* root)
{
  if(root == NULL)
    return NULL;
  while(root->m_pReft)
  {
    root = root->m_pReft;
  }
  return root;
}
BinaryTreeNode* FindMin(BinaryTreeNode*root)
{
  if(root == NULL)
    return NULL;
  while(root->m_pLeft)
  {
    root = root->m_pLeft;
  }
  return root;
}
void  BinaryTreeToDoubleLink(BinaryTreeNode* root)
{
 if(root == NULL)
   return; 
 BinaryTreeToDoubleLink(root->m_pLeft);
 BinaryTreeNode*LeftMax = FindMax(root->m_pLeft);
 BinaryTreeNode*RightMin = FindMin(root->m_pReft);
 if(LeftMax != NULL)
 {
   root->m_pLeft = LeftMax;
   LeftMax->m_pReft = root;
 }
 if(RightMin != NULL)
 {
   root->m_pReft = RightMin;
   RightMin->m_pLeft = root;
 }
 BinaryTreeToDoubleLink(root->m_pReft);
}
int main()
{
}
//方法2
//中序遍历 创建一个变量保存最后一个节点
//if(root->left)
//递归
// root->left = last;
// if(last)
// last->right = root;
//更新last = root
// if(root->right)
// 递归
