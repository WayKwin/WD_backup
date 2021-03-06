#include"BinaryTree.h"
#include<stdio.h>
#include<stddef.h>
#define HEAD \
    do{  \
     printf("\n----------------%s----------------\n",__FUNCTION__); \
    }while(0)
void testParent()
{
    HEAD;
    treeNode* tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    tree = _ConstructTree(tree,pre_str, &index);
    printf("层续遍历结果为\n");
    LevelOrder(tree);
    printf("\n");
    printf("前序遍历结果为\n");
    PreOrder(tree);
    printf("\n");
    treeNode* ret = Parent(tree, tree->left->right->left);
    if(ret != NULL)
        printf("except: E,actual: %c\n", ret->value);
    else
        printf("error\n");
}
void testTreeHeight()
{
    HEAD;
    treeNode* tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    tree = _ConstructTree(tree,pre_str, &index);
    printf("层续遍历结果为\n");
    LevelOrder(tree);
    printf("\n");
    printf("前序遍历结果为\n");
    PreOrder(tree);
    printf("\n");
    size_t ret = TreeHeight(tree);
    printf("except: 4 actual :%zu\n",ret);
}
void testTreeKevelSize()
{
    HEAD;
    treeNode* tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    tree = _ConstructTree(tree,pre_str, &index);
    printf("层续遍历结果为\n");
    LevelOrder(tree);
    printf("\n");
    printf("前序遍历结果为\n");
    PreOrder(tree);
    printf("\n");

   size_t ret =  TreeKLevelSize(tree,3);
   printf(" except:3 actual : %zu \n", ret);
}
void testTreeSize()
{
    HEAD;
    treeNode* old_tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    old_tree = _ConstructTree(old_tree,pre_str, &index);
    int  SizeCount = TreeSize(old_tree);
    printf("except:15 actual: %d\n",SizeCount);

}
void testTreeLeafSize()
{
    HEAD;
    treeNode* old_tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    old_tree = _ConstructTree(old_tree,pre_str, &index);
    int LeafSize = TreeLeafSize(old_tree);
    printf("excpet:8 actual: %d\n",LeafSize);
}
void testTreeClone()
{
    HEAD;
    treeNode* new_tree;
    treeNode* old_tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    old_tree = _ConstructTree(old_tree,pre_str, &index);
    printf("旧树 结果为 :\n");
    printf("层续遍历结果为\n");
    LevelOrder(old_tree);
    printf("\n");
    printf("前序遍历结果为\n");
    PreOrder(old_tree);
    printf("\n");
    new_tree = TreeClone(old_tree);
    printf("新树 结果为 :\n");
    printf("层续遍历结果为\n");
    LevelOrder(new_tree);
    printf("\n");
    printf("前序遍历结果为\n");
    PreOrder(new_tree);
    printf("\n");

}
void testLevelOrder()
{
    HEAD;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    treeNode* node;
    //有返回值的递归 因为有回溯的过程 所以必须有人去接应它
    node = _ConstructTree(node,pre_str,&index );
    printf("层续遍历结果为\n");
    LevelOrder(node);
    printf("\n");
    printf("前序遍历结果为\n");
    PreOrder(node);
    printf("\n");
}
void testConstrcutTree()
{
    HEAD;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    treeNode* node;
    //有返回值的递归 因为有回溯的过程 所以必须有人去接应它
    node = _ConstructTree(node,pre_str,&index );
    printf("前序遍历结果为\n");
    PreOrder(node);
    printf("\n");

}
void testOrderByStack()
{
    HEAD;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    treeNode* node;
    //有返回值的递归 因为有回溯的过程 所以必须有人去接应它
    node = _ConstructTree(node,pre_str,&index );
    printf("前序遍历结果为\n");
    PreOrder(node);
    printf("\n");
    printf("前序遍历bystack 结果为:\n");
    PreOrderByStack(node);
    printf("\n");
    printf("中序遍历结果为\n");
    InOrder(node);
    printf("\n");
    printf("中序遍历bystack 结果为:\n");
    InOrderByStack(node);
    printf("\n");
    printf("后序遍历结果为\n");
    PostOrder(node);
    printf("\n");
    printf("后序遍历bystack _1结果为:\n");
    PostOrderByStack_1(node);
    printf("\n");
    printf("后序遍历bystack _2结果为:\n");
    PostOrderByStack_2(node);
    printf("\n");
}
void testTreeMirror()
{
    HEAD;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    treeNode* node;
    //有返回值的递归 因为有回溯的过程 所以必须有人去接应它
    node = _ConstructTree(node,pre_str,&index );
    printf("前序遍历结果为\n");
    PreOrder(node);
    printf("\n");
    TreeMirror(node);
    printf("翻转之后前序遍历结果为\n");
    PreOrder(node);
    printf("\n");
}
void testIsCompleteTree()
{
    HEAD;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    treeNode* node;
    //有返回值的递归 因为有回溯的过程 所以必须有人去接应它
    node = _ConstructTree(node,pre_str,&index );

    int ret = IsCompleteTree(node);
    if(ret == 1)
        printf("是完全树\n");
    else
        printf("不是完全树\n");

}
void testFindCommonFater()
{
  HEAD;
  treeNode node1;
  treeNode node2;
  treeNode node3;
  treeNode node4;
  treeNode node5;
  treeNode node6;
  treeNode node7;
  node1.value ='1';
  node2.value ='2';
  node3.value ='3';
  node4.value ='4';
  node5.value ='5';
  node6.value ='6';
  node7.value ='7';
  node1.left = &node2;
  node1.right = &node3;
  node2.right = &node5;
  node2.left = &node4;
  node3.left = &node6;
  node3.right = &node7;
  node4.right = node4.left = NULL;
  node5.right = node5.left = NULL;
  node6.right = node6.left = NULL;
  node7.right = node7.left = NULL;
  treeNode* ret = LastCommonFather(&node1,&node4,&node5);
  if(ret != NULL)
    printf("except : 2, act :%c\n",ret->value);
  LevelOrder(&node1);
  PreOrder(&node1);
}
int main()
{
    testFindCommonFater();
    /*testIsCompleteTree();*/
    /*testTreeMirror();*/
    /*testOrderByStack();*/
    /*testParent();*/
    /*testTreeHeight();*/
     /*testTreeKevelSize();*/
    /*testConstrcutTree();*/
    /*testTreeSize();*/
    /*testTreeLeafSize();*/
    /*testTreeClone();*/
    /*testLevelOrder();*/
    /*HEAD;*/
    return 0;
}
