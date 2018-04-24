#include<stdio.h>
#include<stdlib.h>
char* pre_order = "ABDEGCF";
char* in_order = "DBGEACF";
typedef char treeNodeType;
typedef struct _treeNode{
    struct _treeNode* left;
    struct _treeNode* right;
    treeNodeType value;
}treeNode;
treeNode* Construct(char* preorder, char* inorder,int length)
{
    if(preorder == NULL || inorder == NULL)
        return NULL;
    return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}
treeNode* ConstructCore(char* startPreorder,\
        char* endPreorder, char* startInorder, char* endInorder)
{
    char rootValue = startPreorder[0];
    treeNode* root = malloc(sizeof(treeNode));
    root->value  = rootValue;
    root->left = root->right = NULL;
    if(startPreorder == endPreorder)
    {
        if(startPreorder == endInorder && \
                *startPreorder == *startInorder)
        {
            return root;
        }
        else
            return NULL;
    }
    char* rootInorder = startPreorder;
    while(rootInorder <= endInorder && *rootInorder != rootValue)
        ++ rootInorder;
    if(rootInorder == endInorder && *rootInorder != rootValue)
        return NULL;
    int leftLength = rootInorder - startInorder;
    char* leftPreorderEnd = startPreorder + leftLength;
    if(leftLength > 0)
    {
        root->left = ConstructCore(startPreorder + 1,\
                leftPreorderEnd, startInorder, rootInorder - 1);
        if(leftLength < endPreorder - startPreorder)
        {
            root->right = ConstructCore(leftPreorderEnd + 1,
                    endPreorder, rootInorder + 1,endInorder);
        }
    }
    return root;

}
void constructTree_bug(treeNode* node ,char* pre_start,char* pre_end,char*in_start, char* in_end)
{
    if(*pre_start == '\000' || *in_start == '\000')
    {
        free(node);
        node = NULL;
        return;
    }
    treeNodeType root_value = pre_start[0];
    node->value = root_value;
    int offset = 0;
    while(pre_start[0] != in_start[0 + offset])
    {
        offset++;
    }
    if(offset == 0)
      return  ;
    //TODEBUG
    if(offset > 0)
    {
        node->left = malloc(sizeof(treeNode));
        constructTree_bug(node->left,pre_start + 1,pre_start+offset, in_start, in_start+offset - 1);
    }
    if(offset < pre_end - pre_start)
    {
        node->right = malloc(sizeof(treeNode));
        constructTree_bug(node->right,pre_start+offset + 1 , pre_end, in_start + offset + 1, in_end);
    }
}
treeNode* constructTree(treeNode* node ,char* pre_start,char* pre_end,char*in_start, char* in_end)
{
    if(*pre_start == '\000' || *in_start == '\000')
    {
        return NULL;
    }
    node = malloc(sizeof(treeNode));
    treeNodeType root_value = pre_start[0];
    node->value = root_value;
    int offset = 0;
    while(pre_start[0] != in_start[0 + offset])
    {
        offset++;
    }
    if(offset == 0)
    {
        return node ;
    }
    node->left = constructTree(node->left,pre_start + 1,pre_start+offset, in_start, in_start+offset - 1);
    node->right = constructTree(node->right,pre_start+offset + 1 , pre_end, in_start + offset + 1, in_end);
    return node;
}
void pre_order_function(treeNode* root)
{
    if(root == NULL)
        return;
    printf("%c ",root->value);
    pre_order_function(root->left);
    pre_order_function(root->right);
}
void rebulit_tree()
{
    treeNode* root;
    int end = 0;
    while(*(pre_order + end))
    {
        end ++;
    }
    root = constructTree(root,pre_order,pre_order + end - 1, in_order, in_order + end - 1 );
    pre_order_function(root);

}
void rebulit_tree_bug()
{
    treeNode root;
    int end = 0;
    while(*(pre_order + end))
    {
        end ++;
    }
    constructTree_bug(&root,pre_order,pre_order + end - 1, in_order, in_order + end - 1 );
    pre_order_function(&root);
}
int main()
{
    rebulit_tree();
    /*rebulit_tree_bug();*/
}



