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
void Inorder(SearchTreeNode* root);
//两种递归删除形式
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType to_delete);
SearchTreeNode* _SearchTreeRemove(SearchTreeNode* root, SearchTreeType to_delete);
void _SearchTreeInsert_ByLOOP_Version2(SearchTreeNode* root, SearchTreeType key);
void _SearchTreeRemove_ByLoop(SearchTreeNode** proot,SearchTreeType key);
