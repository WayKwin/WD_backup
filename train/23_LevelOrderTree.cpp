#include<iostream>
#include<queue>
using namespace ::std;
struct BinaryTreeNode
{
  int m_nValue;
  BinaryTreeNode* m_pLeft;
  BinaryTreeNode* m_pReft;
};
void LevelOrder(BinaryTreeNode* root)
{
  if(root == NULL)
    return;
  queue<BinaryTreeNode*> q;
  q.push(root);
  while(q.size() != 0)
  {
    BinaryTreeNode* p;
    p = q.front();
    if(p->m_pLeft != NULL)
    {
      q.push(p->m_pLeft);
    }
    if(p->m_pReft != NULL)
    {
      q.push(p->m_pReft);
    }
    cout<< p->m_nValue;
    q.pop();
  }
}
