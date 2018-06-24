#include<iostream>
using namespace::std;
 struct TreeNode {
  int val;
    struct TreeNode *left;
      struct TreeNode *right;
        TreeNode(int x) :
              val(x), left(NULL), right(NULL) {
                }
};
int TreeDepth(TreeNode* pRoot)
{
  if(pRoot == NULL)
    return 0;
  return 1+TreeDepth(pRoot->left) > 1+ TreeDepth(pRoot->right)? 1+TreeDepth(pRoot->left) : 1+TreeDepth(pRoot->right);
}
