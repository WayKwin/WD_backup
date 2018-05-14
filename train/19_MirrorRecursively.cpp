
#include<iostream>
 struct BinaryTreeNode
{
  int m_nValue;
  BinaryTreeNode* m_pLeft;
  BinaryTreeNode* m_pRight;
};
void MirrorRecursively(BinaryTreeNode* root)
{
  // 减少不必要的交换
   if(root == NULL || ( root->m_pLeft == NULL && root->m_pRight == NULL))
     return;
   BinaryTreeNode* temp = root->m_pLeft;
   root->m_pLeft = root->m_pRight;
   root->m_pRight = temp;
   if(root->m_pLeft)
   MirrorRecursively(root->m_pLeft);
   if(root->m_pRight)
   MirrorRecursively(root->m_pRight);
}
