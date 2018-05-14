#include<iostream>
 struct BinaryTreeNode
{
  int m_nValue;
  BinaryTreeNode* m_pLeft;
  BinaryTreeNode* m_pRight;
};
bool Tree1HasTree2(BinaryTreeNode* node1, BinaryTreeNode* node2)
{
   bool flag = false;
   if( node1 == NULL && node2 == NULL )
     return true;
   if( node1 == NULL &&  node2 != NULL )
     return false;
   if( node1 != NULL && node2 == NULL )
     return true;
   if( node1->m_nValue != node2->m_nValue )
   {
     return false;
   }
   if(node1->m_nValue == node2->m_nValue)
   {
      return true;
   }
    flag = Tree1HasTree2(node1->m_pLeft, node2->m_pLeft);
  if(flag == true)
  {
    flag = Tree1HasTree2(node1->m_pRight, node2->m_pRight);
  }
  //可以return  left && right
  return flag;
}
bool HasSubtree(BinaryTreeNode*node1,BinaryTreeNode* node2)
{
  if(node1 == NULL && node2 == NULL)
    return true;
  if(node1 == NULL && node2 != NULL)
    return false;
  if( node1 != NULL && node2 == NULL )
    return true;
  int flag = Tree1HasTree2(node1, node2);
  if( flag == false )
  {
    flag = Tree1HasTree2(node1->m_pLeft, node2); 
  }
  if( flag == false )
  {
    flag = Tree1HasTree2(node1->m_pRight, node2);
  }
  return flag;
}
