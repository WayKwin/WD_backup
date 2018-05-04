#include"BinaryTree.h"
void TreeInit(treeNode** node)
{
    if(node == NULL)
        return;
    *node = (treeNode*)malloc(sizeof(treeNode));
    ( *node )->left = NULL;
    ( *node )->right = NULL;
}
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
void ConstructTree(treeNode* node,char * str, int* index)
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
    if(node->left == NULL)
        perror("malloc:");
    (*index)++;
    ConstructTree(node->left, str,index);
    node->right = malloc(sizeof(treeNode));
    if(node->right == NULL)
        perror("malloc:");
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
        return NULL;
       /*treeNode*  new_node = (treeNode*)malloc(sizeof(treeNode));*/
        /*new_node->value = *( str + *index );*/
        /*return new_node;*/
    }
    node = (treeNode*)malloc(sizeof(treeNode));
    if(node == NULL)
        perror("malloc:");
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
void InOrder(treeNode* node)
{
    if( node == NULL )
        return;
    InOrder(node->left);
    printf("%c ",node->value);
    InOrder(node->right);

}
void PostOrder(treeNode* node)
{
    if( node == NULL )
        return;
    PostOrder(node->left);
    PostOrder(node->right);
    printf("%c ",node->value);

}
treeNode* TreeClone(treeNode* old)
{
    if(old == NULL)
        return NULL;
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    if(node == NULL)
        perror("malloc:");
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
size_t _TreeKLevelSize(treeNode* root,int k,int deep_count)
{
    //应该先判断是否为空
    //否则空节点会return 1
    /*if(k == deep_count)*/
        /*return 1;*/
    /*else if(root == NULL || deep_count > k)*/
        /*return 0;*/
    if(root == NULL || deep_count > k)
        return 0;
    if(k == deep_count)
        return 1;
     return _TreeKLevelSize(root->left,k,deep_count + 1) + _TreeKLevelSize(root->right,k,deep_count + 1);
}
size_t TreeKLevelSize(treeNode* root, int k)
{
    if( root == NULL || k ==  0)
        return -1;
    if(root == NULL || k < 0)
        return 0;
    if( k == 1 )
        return 1;
    return TreeKLevelSize(root,k - 1) + TreeKLevelSize(root, k - 1);
}
size_t TreeHeight(treeNode* root)
{
   if(root == NULL)
       return 0;
   int left_count = 1 + TreeHeight(root->left);
   int right_count = 1 + TreeHeight(root->right);
   return left_count > right_count ? left_count : right_count;
}
treeNode* _TreeFind(treeNode* root, treeNodeType to_find)
{
    treeNode* to_ret = NULL;
    if(root == NULL)
        return NULL;
    if(root->value == to_find)
        return root;
    to_ret = _TreeFind(root->left, to_find);
    if(to_ret == NULL)
        to_ret = _TreeFind(root->right, to_find);
    return to_ret;
}
treeNode* LChild(treeNode* node)
{
    if(node == NULL)
    {
        printf("invalid input\n");
        return NULL;
    }
    return node->left;
}
treeNode* RChild(treeNode* node)
{
    if(node == NULL)
    {
        printf("invalid input\n");
        return NULL;
    }
    return node->right;
}
treeNode* TreeFind(treeNode* root, treeNodeType to_find)
{
    treeNode* node = _TreeFind(root, to_find);
    return node;
}
treeNode* Parent(treeNode* root, treeNode* node)
{
    if(root == NULL || node == NULL)
        return NULL;
    treeNode* Parent_Node = NULL;
    if(root->left == node || root->right == node)
        return root;
    Parent_Node = Parent(root->left, node);
    if(Parent_Node == NULL)
        Parent_Node = Parent(root->right, node);
    return Parent_Node;
}
void StackInit(stack* s)
{
    if(s == NULL)
    {
        printf("invalid input \n");
        return;
    }
    s->top = s->base = 0;
}
void StackPush(stack* s, StackType key)
{
    if(s == NULL)
        return;
    s->array[++s->top] = key;
}
StackType StackPop(stack* s)
{
    if(s == NULL)
        return NULL;
    if(s->top == s->base)
        return NULL;
    if(s->base == s->top)
    {
        printf(" empty stack \n");
        return NULL;
    }
    return s->array[s->top--];
}
StackType StackTop(stack* s)
{
    return s->array[s->top];
}
int StackEmpty(stack* s)
{
    if(s->base == s->top)
       return 1;
    return 0;
}

void PreOrderByStack(treeNode* root)
{
    stack s;
    StackInit(&s);
    if(root == NULL)
        return;
    treeNode* cur = root;
    while(!StackEmpty(&s) ||  cur != NULL)
    {
        while(cur != NULL)
        {
            printf("%c ",cur->value);
            StackPush(&s, cur);
            cur = cur->left;
        }
        //发现cur走到NULL 回退一步
        //因为回退一步已经走过了,所以把其出栈
        //在看其右子树有没有节点
        if(!StackEmpty(&s))
        {
            cur = StackTop(&s);
            StackPop(&s);
            cur = cur->right;
        }

    }
}
void InOrderByStack(treeNode* root)
{
    if(root == NULL)
    {
        printf("empty tree\n");
        return;
    }
    stack s;
    StackInit(&s);
    treeNode* cur = root;
    while(!StackEmpty(&s) || cur != NULL)
    {
        while(cur != NULL)
        {
            StackPush(&s,cur);
            cur = cur-> left;
        }
        if(!StackEmpty(&s))
        {
            cur = StackTop(&s);
            printf("%c ", cur->value);
            StackPop(&s);
            cur = cur->right;
        }
    }
}
#if 1
void PostOrderByStack_1(treeNode* root)
{
    stack s;
    StackInit(&s);
    int frist_in_top = 0;
    treeNode* cur = root;
    while(!StackEmpty(&s) || cur != NULL)
    {
        while(cur != NULL)
        {
            cur->IsFristInStack = 1;
            StackPush(&s,cur);
            cur = cur->left;
        }
        if(!StackEmpty(&s))
        {
            cur = StackTop(&s);
            if(cur->IsFristInStack == 1)
            {
                cur->IsFristInStack = 0;
                cur = cur->right;
            }
            //走到这表明右子树也走完了
            else
            {
                printf("%c ",cur->value);
                StackPop(&s);
                //因为是左右子树都访问完了才打印的根节点,
                //所以让cur = NULL 避免重复走
                //当cur = NULL 第一个循环就进不去
                //而是直接判断栈是否为空
                cur = NULL;
            }
        }
    }
}
#endif
void PostOrderByStack_2(treeNode* root)
{
    // 入栈的时候先入根节点,然后入右节点,再入左节点  当出栈的时候就可以后续出栈了
    // A B C 入栈 A C  B   出栈   B  C  A
    // 如果 node 左右都为空 打印node 并且出栈
    // 因为node入栈的顺序 top 先是左子树 然后是右子树 最后是根节点
    // 如果 node 的左右节点任何一个被被访过了,那么node 也可以出栈 很巧妙
    if( root == NULL)
        return ;
    stack s;
    StackInit(&s);
    treeNode* cur ;
    StackPush(&s, root);
    //跟踪上次访问的节点
    treeNode* pre = NULL;
    while( !StackEmpty(&s))
    {
        cur = StackTop(&s);
        if( ( cur->left == NULL &&  cur->right == NULL ) || \
            ( ( pre != NULL ) && ( cur->left == pre || cur->right == pre ) ))
        {
            printf("%c ",cur->value);
            //记得能打印的就应该pop
            StackPop(&s);
            //记得跟新pre
            pre = cur;
        }
        else
        {
            //注意入栈顺序
            //先右后左
            if( cur->right != NULL )
                StackPush(&s,cur->right);
            if(cur->left != NULL)
                StackPush(&s, cur->left);
        }
    }
}
void TreeMirror(treeNode* root)
{
    if( root == NULL )
        return;
    treeNode* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    TreeMirror(root->left);
    TreeMirror(root->right);
}
int IsCompleteTree(treeNode* root)
{
    if(root == NULL)
        return -1;
    int SingleChild_flag = 0;
    int ReachLeaf_flag = 0;
    queue q;
    queueInit(&q);
    queuePush(&q,root);
    while(queueHead(&q) != NULL)
    {
        if( ReachLeaf_flag == 1  )
        {
            if(queueHead(&q)->left != NULL || queueHead(&q)-> right != NULL)
                return 0;
        }
        if(SingleChild_flag == 1)
        {
            if(queueHead(&q)->right != NULL || queueHead(&q)->left != NULL)
                return 0;
        }
        //只有右节点
       if(queueHead(&q)->right != NULL && queueHead(&q)->left == NULL)
           return 0;
       //只有左节点
       else if( queueHead(&q)->left != NULL && queueHead(&q)->right == NULL )
       {
           SingleChild_flag = 1;
           ReachLeaf_flag = 1;
           queuePush(&q,queueHead(&q)->left);
           queueFront(&q,NULL);
           continue;
       }
       //叶子节点
       else if(queueHead(&q)->right == NULL && queueHead(&q)->left == NULL)
       {
           ReachLeaf_flag = 1;
           queueFront(&q,NULL);
           continue;
       }
       //有左右节点
       else
       {
           queuePush(&q,queueHead(&q)->left);
           queuePush(&q,queueHead(&q)->right);
           queueFront(&q,NULL);
       }
    }
    return 1;
}
