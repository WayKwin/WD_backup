#include<stdio.h>
#include<stdlib.h>
typedef char treeNodeType;
typedef struct _treeNode{
    struct _treeNode* left;
    struct _treeNode* right;
    treeNodeType value;
}treeNode;
// 输入数组(数组的每个元素是树上的节点),
/*
 *  a b # # #
 *
 */
void ConstructTree(treeNode* node,char * str)
{
    if(str == NULL)
        return;
    if(*str == '#')
    {
        free(node);
        node = NULL;
        return;
    }
    node->value = *str;
    node->left = malloc(sizeof(treeNode));
    ConstructTree(node->left, ++str);
    node->right = malloc(sizeof(treeNode));
    ConstructTree(node->right, ++str);
}
void PreOrder(treeNode* node)
{
    if( node == NULL )
        return;
    printf("%c ",node->value);
    PreOrder(node->left);
    PreOrder(node->right);
}
treeNode root;
int main()
{
    char* pre_str = "ABC##D#EF#G";
    ConstructTree(&root,pre_str );
    PreOrder(&root);
    return 0;
}
