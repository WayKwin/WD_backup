#include<iostream>
#include<queue>
using namespace::std;
 struct TreeNode {
         int val;
          TreeNode *left;
           TreeNode *right;
            TreeNode(int x) : val(x), left(NULL), right(NULL) {}
         };
   
bool IsBalanced_Solution(TreeNode* pRoot) {
   if(pRoot == NULL)
     return true;
  queue<TreeNode*> help;
  TreeNode* cur = pRoot;
  help.push(cur);
  bool reach_single = false;
  bool reach_left = false;
  while(!help.empty())
  {
    cur = help.front();
    if(reach_left== true)
    {
      reach_single = true;
    }
    if(reach_single == true)
    {
      if( cur->left ||  cur->right)
      {
        return false;
      }
    }
    if(cur->right && !cur->left)
    {
      return false;
    }
    else if(cur->left && !cur->right)
    {
      reach_left= true;
      help.push(cur->left);
    }
    else if(!cur->right  && !cur->right)
    {
      reach_single = true;
    }
    else 
    {
      help.push(cur->left);
      help.push(cur->right);
    }
    help.pop();
  }
  return true;
 }
int main()

{

}
