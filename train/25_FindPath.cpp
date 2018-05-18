#include<iostream>
//#include<stack>
#include<list>
//其实用vector更好,(使用vector模拟stack而且可以随意遍历)
using namespace::std;
struct BinaryTreeNode
{
  int m_nValue;
  BinaryTreeNode* m_pLeft;
  BinaryTreeNode* m_pReft;
};
void  FindPath(BinaryTreeNode*root, int sum,int& CurrentSum,list<int> Path)
{
 if(root == NULL )
 {
   return;
 }
 CurrentSum += root->m_nValue;
 Path.push_back(root->m_nValue);
 if(CurrentSum == sum)
 {
   cout << "find a path"<<endl;
   auto iter = Path.begin();
   while(iter != Path.end())
   {
      cout<< *iter << " ";
      iter++;
   }
   cout << endl;
 }
 else if(CurrentSum > sum)
 {
   return;
 }
  FindPath(root->m_pLeft,sum,CurrentSum,Path);
  FindPath(root->m_pReft,sum,CurrentSum,Path);
  //左右子树走完 把这个节点出队列
  CurrentSum -= Path.back();
  Path.pop_back();
}
int main()
{
  BinaryTreeNode node10;
  BinaryTreeNode node5;
  BinaryTreeNode node4;
  BinaryTreeNode node7;
  BinaryTreeNode node12;
  node10.m_nValue = 10;
  node5.m_nValue = 5;
  node4.m_nValue = 4;
  node7.m_nValue = 7;
  node12.m_nValue = 12;

  node10.m_pLeft = &node5;
  node10.m_pReft= &node12;
  node5.m_pLeft = &node4;
  node5.m_pReft= &node7;

  node4.m_pLeft = NULL;
  node4.m_pReft = NULL;
  node7.m_pLeft = NULL;
  node7.m_pReft = NULL;
  node12.m_pLeft = NULL;
  node12.m_pReft = NULL;

  list<int> list;

  int CurrentSum = 0;
  FindPath(&node10,22,CurrentSum,list);

}
