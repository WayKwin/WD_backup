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
treeNode root;
void constructTree(treeNode* node ,char* pre_start,char* pre_end,char*in_start, char* in_end)
{
    int i = 0;
    treeNodeType root_value = pre_start[0];
    node->value = root_value;
    int offset = 0;
    while(pre_start[0+offset] != in_end[0 + offset])
    {
        offset++;
    }
    if(offset == 0)
      return  ;
    //TODEBUG
    node->left = malloc(sizeof(treeNode));
    constructTree(node->left,pre_start,pre_start+offset, in_start,in_start+offset);
    node->right = malloc(sizeof(treeNode));
    constructTree(node->right,pre_start+offset+1,pre_end, in_start + offset + 1, in_end);
}
int main()
{
    int end = 0;
    while(*(pre_order + end))
    {
        end ++;
    }

    constructTree(&root,pre_order,pre_order + end - 1, in_order, in_order + end - 1 );

}



