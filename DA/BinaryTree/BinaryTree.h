#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
typedef char treeNodeType;
typedef struct _treeNode{
    struct _treeNode* left;
    struct _treeNode* right;
    treeNodeType value;
#if 1
    int IsFristInStack;
#endif
}treeNode;
typedef struct _queue
{
    treeNode* data[MAX_SIZE];
    int size;
    int head;
    int tail;
}queue;
typedef treeNode*  StackType;
typedef struct _stack
{
    StackType array[MAX_SIZE];
    size_t base;
    size_t top;
}stack;
    void InOrder(treeNode* node);
    void PostOrder(treeNode* node);
    void ConstructTree(treeNode* node,char * str, int* index);
    treeNode* LChild(treeNode* node);
    void LevelOrder(treeNode* node) ;
    void InOrderByStack(treeNode* root);
    treeNode* Parent(treeNode* root, treeNode* node);
    void PostOrderByStack_1(treeNode* root);
    void PostOrderByStack_2(treeNode* root);
    void PreOrder(treeNode* node);
    void PreOrderByStack(treeNode* root) ;
    treeNode* RChild(treeNode* node);
    int StackEmpty(stack* s);
    void StackInit(stack* s);
    StackType StackPop(stack* s);
    void StackPush(stack* s, StackType key);
    StackType StackTop(stack* s);
    treeNode* TreeClone(treeNode* old);
    treeNode* TreeFind(treeNode* root, treeNodeType to_find) ;
    size_t TreeHeight(treeNode* root);
    void TreeInit(treeNode** node);
    size_t TreeKLevelSize(treeNode* root, int k);
    size_t TreeLeafSize(treeNode* root);
    size_t TreeSize(treeNode* root);
    treeNode* _ConstructTree(treeNode* node, char* str, int *index);
    treeNode* TreeFind(treeNode* root, treeNodeType to_find) ;
    size_t _TreeKLevelSize(treeNode* root,int k,int deep_count);
    void queueFront(queue* q, treeNode* n)                   ;
    treeNode*  queueHead(queue*q);
    void queueInit(queue* q);
    void queuePush(queue* q,treeNode* n );
    void TreeMirror(treeNode* root);
    int IsCompleteTree(treeNode* root);
    int IsBalanceTree(treeNode* Node);
////////////////////////////////////////
// interview
// ////////////////////////////////////
    treeNode* LastCommonFather(treeNode*root, treeNode* node1,treeNode*node2);
#endif
