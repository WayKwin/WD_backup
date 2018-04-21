#include<stdio.h>
#include<ctype.h>
#include<malloc.h>
typedef char key_t;
typedef struct _node
{
    struct _node* left;
    struct _node* right;
    key_t value;
}node;
node tree;
/*void _polish(node* node, char* str)*/
/*{*/

    /*node->value = *str;*/
    /*//注意不能让字符串来回递归*/
    /*if(str == NULL || isalnum(node->value) )*/
        /*return ;*/
         /*node->left = malloc(sizeof(struct _node));*/
         /*_polish(node->left, ++str);*/
         /*node->right = malloc(sizeof(struct _node));*/
        /*_polish(node->right, ++str);*/
/*}*/
/*void _polish(node* node_t, char* str)*/
/*{*/

    /*node->value = *str;*/
    /*//注意不能让字符串来回递归*/
    /*if(str == NULL || isalnum(node->value) )*/
        /*return ;*/
         /*node->left = malloc(sizeof(struct _node));*/
         /*_polish(node->left, ++str);*/
         /*node->right = malloc(sizeof(struct _node));*/
        /*_polish(node->right, ++str);*/
/*}*/
//要用非递归实现二叉树的插入,必然要记录之间的节点 才能回溯
//所以递归和非递归都要消耗时间空间复杂度
//而斐波那契数列的以前状态 只需要 两个就能确定 所以空间复杂度是o(1)
//一些动态规划也要消耗空间复杂度来记录每次之前的状态 方便你以后的状态进行回溯查找
//例如最长子序列和01背包
/*void _polish_(node* node_t,char* str)*/
/*{*/
    /*while(*str)*/
    /*{*/
        /*node* node_backup = node_t;*/
        /*if(!isalnum(*str))*/
        /*{*/
            /*node_t = malloc(sizeof(node));*/
            /*node_t = node_t->left;*/
        /*}*/
        /*else*/
        /*{*/
            /*node_t = malloc(sizeof(node));*/
            /*node_t = node_backup;*/
            /*node_t = node_t->right;*/
        /*}*/
            /*str++;*/
    /*}*/

/*}*/
void afterPrint(node* node)
{
    if(node == NULL)
        return;
    afterPrint(node->left);
    afterPrint(node->right);
    printf("%c,",node->value);
}
void middlePrint(node* node)
{
    if(node == NULL)
        return;
    middlePrint(node->left);
    printf("%c,",node->value);
    middlePrint(node->right);
}
void Polish(node* root, char* str)
{
    if(str == NULL )
        return;
    _polish_(root,str);
    middlePrint(root);
    printf("\n");
    afterPrint(root);
    printf("\n");
}
char* b = "-+a*+bcde";
int main()
{
    /*char* b = "-+a*+baaa";*/
    Polish(&tree,b);
}
