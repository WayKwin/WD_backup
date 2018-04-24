#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#define HEAD \
    do{  \
     printf("\n----------------%s----------------\n",__FUNCTION__); \
    }while(0)
typedef char treeNodeType;
typedef struct _treeNode{

    struct _treeNode* left;
    struct _treeNode* right;
    treeNodeType value;
}treeNode;
void TreeInit(treeNode** node)
{
    if(node == NULL)
        return;
    *node = (treeNode*)malloc(sizeof(treeNode));
    ( *node )->left = NULL;
    ( *node )->right = NULL;
}
#define MAX_SIZE 100
typedef struct _queue
{
    treeNode* data[MAX_SIZE];
    int size;
    int head;
    int tail;
}queue;
void queueInit(queue* q)
{
    if(q == NULL)
        return;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}
void queuePush(queue* q,treeNode* n )
{
    if(q == NULL || n == NULL )
        return;
    if(q->head == q->tail && q->size == MAX_SIZE)
        return;
    q->data[q->tail++] = n;
    q->tail%=MAX_SIZE;
    q->size++;
}
void  queueFront(queue* q, treeNode* n)
{
    if(q == NULL )
        return;
    if(q->size == 0)
        return;
    if(n == NULL)
        q->head++;
    else
        //注意解引用..
        *n = *q->data[q->head++] ;
    q->head%=MAX_SIZE;
    q->size--;
}
treeNode* queueHead(queue*q)
{
    if(q == NULL )
        return NULL;
    if(q->size == 0)
        return NULL;
    return q->data[q->head] ;
}

void LevelOrder(treeNode* node)
{
    if(node == NULL)
        return;
    queue q;
    queueInit(&q);
    queuePush(&q, node);
    treeNode ret;
    while(1)
    {
        if(q.size == 0)
            break;
        if(queueHead(&q)->left != NULL)
            queuePush(&q,queueHead(&q)->left);
        if(queueHead(&q)->right != NULL);
            queuePush(&q,queueHead(&q)->right);
        /*printf("%c ", queueHead(&q)->value);*/
        queueFront(&q,&ret);
        printf("%c ",ret.value);
    }
}
// 输入数组(数组的每个元素是树上的节点),
/*
 *  a b # # #
 *
 */
// 传指针每次都能改变index,即使return index还是线性增加
void ConstructTree(treeNode* node,char * str, int * index)
{
    if(( str+*index  )== '\000')
    {
        free(node);
        node = NULL;
        return;
    }
    if(*(str+*index ) == '#')
    {
        node->value = *( str + *index );
        return;
    }
    node->value = *( str + *index );
    node->left = malloc(sizeof(treeNode));
    (*index)++;
    ConstructTree(node->left, str,index);
    node->right = malloc(sizeof(treeNode));
    (*index)++;
    ConstructTree(node->right, str,index);
}
treeNode*  _ConstructTree(treeNode* node, char* str, int *index)
{
    if(( str+*index  )== '\000')
    {
        return NULL;
    }
    if(*(str+*index ) == '#')
    {
       treeNode*  new_node = (treeNode*)malloc(sizeof(treeNode));
        new_node->value = *( str + *index );
        return new_node;
    }
    node = (treeNode*)malloc(sizeof(treeNode));
    node->value = *( str + *index );
    (*index)++;
    node->left = _ConstructTree(node->left, str, index);
    (*index)++;
    node->right= _ConstructTree(node->right, str, index);
    return node;
}
void PreOrder(treeNode* node)
{
    if( node == NULL )
        return;
    printf("%c ",node->value);
    PreOrder(node->left);
    PreOrder(node->right);
}
treeNode* TreeClone(treeNode* old)
{
    if(old == NULL)
        return NULL;
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    node->value = old->value;
    node->left = TreeClone(old->left);
    node->right = TreeClone(old->right);
    return node;
}
size_t TreeSize(treeNode* root)
{
    if(root == NULL)
        return 0;
    return 1 + TreeSize(root->left) + TreeSize(root->right);
}
size_t TreeLeafSize(treeNode* root)
{
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return 1;
    else
        //递归求树左子树和右子树中 叶子节点
        return TreeLeafSize(root->left) + TreeLeafSize(root->right);
}
/*
 *
 *
 *
 *unit test
 */
void testTreeSize()
{
    HEAD;
    treeNode* old_tree;
    char* pre_str = "ABD##EG###C#F##";
    int index = 0;
    old_tree = _ConstructTree(old_tree,pre_str, &index);
    int  SizeCount = TreeSize(old_tree);
    printf("excpet:15 actual: %d\n",SizeCount);

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
int main()
{
    testTreeSize();
    /*testTreeLeafSize();*/
    /*testTreeClone();*/
    /*testLevelOrder();*/
    /*HEAD;*/
    return 0;
}
