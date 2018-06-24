#include<iostream>
#include<vector>
#include<queue>
using namespace::std;
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
 val(x), left(NULL), right(NULL) {
        
 }
};
vector<vector<int> > Print(TreeNode* pRoot) {
  queue<TreeNode*> help;
  vector<vector<int> > ret;
  vector<int> level;
  TreeNode* cur = pRoot;
  help.push(pRoot);
  level.push_back(cur->val);
  ret.push_back(level);

  while(!help.empty())
  {
    help.pop();
    vector<int> tmp;

    if(cur->left)
    {
      tmp.push_back(cur->left->val);
      help.push(cur->left);
    }
    if(cur->right)
    {
      tmp.push_back(cur->right->val);
      help.push(cur->right);
    }
    if(!tmp.empty())
    {
      ret.push_back(tmp);
    }
    cur = help.front();
  }
  return ret; 
}

bool isSymmetrical(TreeNode* pRoot)
{
  if(pRoot == NULL)
    return false;
  queue<TreeNode*> help;
  help.push(pRoot);
  TreeNode* cur = help.front();
  while(!help.empty())
  {
    if(cur->left && cur->right)
    {
      help.push(cur->left); 
      help.push(cur->right); 
    }
    
  }
  

}


int main()
{
  TreeNode t1(1);
  TreeNode t2(2);
  TreeNode t3(3);
  TreeNode t4(4);
  TreeNode t5(5);
  TreeNode t6(6);
  TreeNode t7(7);
  t1.left = &t2;
  t1.right = &t3;
  t2.left= &t4;
  t2.right = &t5;
  t3.left= &t6;
  t3.right = &t7;
  vector<vector<int> > ret = Print(&t1);
  int i = 0;
  int j = 0;
  for( ;i < ret.size(); i++ )
  {
    for(j = 0; j < ret[i].size();j++)
    {
        printf("%d ",ret[i][j]);
     }
    printf("\n");
  }

}
