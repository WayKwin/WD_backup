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
void _polish(node* node, char* str)
{

    node->value = *str;
    //注意不能让字符串来回递归
    if(str == NULL || isalnum(node->value) )
        return ;
         node->left = malloc(sizeof(struct _node));
         _polish(node->left, ++str);
         node->right = malloc(sizeof(struct _node));
        _polish(node->right, ++str);
}
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
    _polish(root,str);
    middlePrint(root);
    printf("\n");
    afterPrint(root);
    printf("\n");
}
int main()
{
    char* b = "-+a*+bcde";
    /*char* b = "-+a*+baaa";*/
    Polish(&tree,b);
}
