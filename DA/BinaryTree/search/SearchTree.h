#pragma once
#include<stdio.h>
typedef char SearchTreeType;
typedef struct SearchTreeNode
{
  SearchTreeType key;
  struct SearchTreeNode* lchild;
  struct SearchTreeNode* rchild;
}SearchTreeNode;
void SearchTreeInit(SearchTreeNode** root,SearchTreeType key);
void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key);
SearchTreeNode* SearchTreeFind(SearchTreeNode** root, SearchTreeType to_find);
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key);
void Inorder(SearchTreeNode* root);
