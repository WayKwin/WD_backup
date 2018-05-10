#include"maze.h"
//初始化迷宫
void MazeInit(Maze* maze)
{
    int map[MAX_ROW][MAX_COL] =
    {
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 }
    };
    int i;
    int j;
    for( i = 0; i < MAX_COL; i++ )
    {
        for( j = 0; j < MAX_COL;j++ )
        {
            maze->map[i][j] = map[i][j];
        }
    }
}
//printf一行中 %2d
void MazePrint(const Maze* maze)
{
    if(maze == NULL)
        return;
    int i,j;
    for(i = 0; i < MAX_ROW; i++)
    {
        for(j = 0; j < MAX_COL; j++)
        {
            printf("%2d ",maze->map[i][j]);
        }
        printf("\n");
    }
        printf("\n");
}
//////////////////////////////////////////
//Round1 递归方式来解决迷宫问题
/////////////////////////////////////////
//
int  CanStay(Maze* maze, Point cur)
{
    if(maze == NULL)
        return 0;
    if(cur.row < 0 || cur.row >= MAX_ROW || cur.col < 0 || cur.col >= MAX_COL)
    {
        return 0;
    }
    //2 3 都能走
    //
    /*if(maze->map[cur.row][cur.col] == 0 && maze->map[cur.row][cur.col] == 2)*/
    /*{*/
        /*return 0;*/
    /*}*/
    //1能走
    if(maze->map[cur.row][cur.col] == 1)
    {
        return 1;
    }
    return 0;
}
void Mark(Maze* maze, Point cur)
{
    maze->map[cur.row][cur.col] = 3;
}
int  IsExit(Maze* maze, Point cur, Point entry )
{
    //出口就是入口
    if(( cur.row == entry.row ) && (cur.col == entry.col))
        return 0;
    if(cur.row == 0 || cur.col == 0 || cur.row == MAX_ROW - 1 || cur.col == MAX_COL - 1)
        return 1;
    else
        return 0;

}

////////////////////////////////////////
//Round2 手动记录栈
///////////////////////////////////////
void PointStackInit(PointStack* ps)
{
    ps->size = 0;
}
void PointStackPush(PointStack* ps,Point p)
{
    if( ps == NULL )
        return;
    if(ps->size == MAX_POINTSTACK )
        return;
    ps->p[ps->size++] = p;
}
void PointStackPop(PointStack* ps,Point* p)
{
    if(ps == NULL)
        return;
    if(ps->size == 0)
    {
        return;
    }
    if( p != NULL )
        *p = ps->p[ps->size--];
    else
        ps->p[ps->size--];
}
Point* PointStackTop(PointStack*ps)
{
    if(ps == NULL)
        return NULL;
    if(ps->size == 0)
    {
        return NULL;
    }
    return ps->p+ps->size - 1;
}
void PointStackDebugPrint(PointStack * stack, const char*msg)
{
    printf("[%s]\n",msg);
    size_t i = 0;
    for(; i < stack->size; i++)
    {
        printf("(%d, %d)",stack->p[i].row,stack->p[i].col);
    }
    printf("\n");
    //打印顺序表
}
void PointStackAssgin(PointStack* stack_dst, PointStack* stack_src)
{
    if(stack_src == 0 || stack_dst == 0)
        return;
    int i = 0;
    for(; i < stack_src->size; i++)
    {
        stack_dst->p[i] = stack_src->p[i];
    }
    stack_dst->size = stack_src->size;
}

void GetPathByLoop(Maze* maze, Point entry)
{
    PointStack ps;
    PointStackInit(&ps);
    Point p = entry;
    PointStackPush(&ps,p);
    while(PointStackTop(&ps) != NULL)
    {
        if(IsExit(maze,p,entry))
        {
            PointStackDebugPrint(&ps,"路径");
            PointStackPop(&ps,NULL);
        }
        p.row -= 1;
        PointStackPush(&ps,p);
        if(CanStay(maze,p))
        {
            Mark(maze,p);
            continue;
        }
        else
        {
            PointStackPop(&ps,NULL);
            if(PointStackTop(&ps) != NULL)
            p = *PointStackTop(&ps);
            else break;
        }

        p.col += 1;
        PointStackPush(&ps,p);
        if(CanStay(maze,p))
        {
            Mark(maze,p);
            continue;
        }
        else
        {
            PointStackPop(&ps,NULL);
            if(PointStackTop(&ps) != NULL)
            p = *PointStackTop(&ps);
            else break;
        }

        p.row += 1;
        PointStackPush(&ps,p);
        if(CanStay(maze,p))
        {
            Mark(maze,p);
            continue;
        }
        else
        {
            PointStackPop(&ps,NULL);
            if(PointStackTop(&ps) != NULL)
            p = *PointStackTop(&ps);
            else break;
        }

        p.col -= 1;
        PointStackPush(&ps,p);
        if(CanStay(maze,p))
        {
            Mark(maze,p);
            continue;
        }
        else
        {
            PointStackPop(&ps,NULL);
            if(PointStackTop(&ps) != NULL)
            p = *PointStackTop(&ps);
            else break;
        }
        PointStackPop(&ps,NULL);
     }
    MazePrint(maze);
    Point* ret ;
}

    //2 判定入口能否落脚
    //3 标记入口点,并且入口点入栈
    //栈为空说明回溯结束了
    //4 进行循环,获取到当前的栈顶元素
    //5 判定这个当前点是否能落脚
    //6 进行判定
    //可以走 continue;
    //7 判定这个电是不是出口,如果是出口,直接函数返回
    //8 按照顺时针方向取相邻点,判定相邻点是否能落脚,
    //      如果能落脚,就标记并且入站,立刻进入下一轮循环
    //9如果四个向领的点都不能落脚,就出战当前点,相当于回溯


////////////////////////////////////////////////////////////
//Round3 如果迷宫有多条路径,找到其中的最短路径
///////////////////////////////////////////////////////////


void GETPATH(Maze* maze,Point cur,Point entry, PointStack* cur_path, PointStack* short_path)
{
    //1.如果能落脚,对当前点标记,同时把当前点插入 cur_path
    Point p = cur;
    if(!CanStay(maze,p))
    {
        return;
    }
    Mark(maze,p);
    PointStackPush(cur_path,p);
    //2.判定当前点是否是出口
    if(IsExit(maze,p,entry))
    {
        printf("找到了一条路径:\n");
        PointStackDebugPrint(cur_path,"路径");
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            printf("找到了目前最短的路径\n");
            PointStackAssgin(short_path, cur_path);
        }
        //到出口就应该回溯,不管是不是目前最小的
        PointStackPop(cur_path,NULL);
        return;
    }
    //不是出口
    Point up = cur;
    up.row -= 1;
    GETPATH(maze, up, entry, cur_path, short_path);
    Point right = cur;
    right.col += 1;
    GETPATH(maze, right, entry, cur_path, short_path);
    Point down =cur;
    down.row += 1;
    GETPATH(maze, down, entry, cur_path, short_path);
    Point left =cur;
    left.col -= 1;
    GETPATH(maze, left, entry, cur_path, short_path);

    PointStackPop(cur_path, NULL);
   //3.如果是出口
    //  size;
    //  a)和short_path比较,若short_path空或者比short_path短代替完毕也需要回溯
    //  b)如果当前路径没有比shortpath端,尝试其他路径在回溯之前,要把cur_path栈顶元素出栈(没戏往回退一个)
    //4. 当前点不是出口,探测四个方向
    //5.如果四个方向都递归探测过,出栈(没戏往回退)当前栈帧结束,回溯上一点;
    //就像最长子序列 ,递归无法获得轨迹
    //因为返回值就一个
    // n-1 只能获得 n的一个状态(之后会被覆盖)
    //实际上是把能走1的都走完,是一种遍历
}

void MazeInitShortPath(Maze* maze)
{
     int map[MAX_ROW][MAX_COL] =
    {
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 }
    };
    int i;
    int j;
    for( i = 0; i < MAX_COL; i++ )
    {
        for( j = 0; j < MAX_COL;j++ )
        {
            maze->map[i][j] = map[i][j];
        }
    }

}

//用栈保存路径
//找到所有路径,之后筛选出最短路径
// 两个栈,一个保存当前路径,一个保存最小路径 (选择排序)
void GetShortPath(Maze* maze,Point entry)
{
    //递归版本
    PointStack cur_path;
    PointStack short_path;
    PointStackInit(&cur_path);
    PointStackInit(&short_path);
    GETPATH(maze, entry, entry, &cur_path, &short_path);
    PointStackDebugPrint(&short_path,"最短路径为");
    //使用递归版本函数 后面两个参数 是两个栈
    //
    //打印函数
}
/*int main() { [>PointStack cur_path;*/ /*PointStack short_path;*/ /*PointStackInit(&cur_path);*/ /*PointStackInit(&short_path);*/ /*Point p1 ={ 1, 2 };*/ /*Point p2 ={ 3, 4 };*/ /*Point p3 ={ 5, 6 };*/ /*PointStackPush(&cur_path,p1);*/ /*PointStackPush(&cur_path,p2);*/ /*PointStackPush(&cur_path,p3);*/ /*PointStackAssgin(&short_path, &cur_path);*/ /*PointStackDebugPrint(&short_path,"最短路径为");<] Maze maze; Point entry; entry.row = 0; entry.col = 2; MazeInitShortPath(&maze); MazePrint(&maze);*/
    /*GetShortPath(&maze,entry);*/
    /*MazePrint(&maze);*/
    /*return 0;*/
/*}*/
////////////////////////////////////////////////////////////
//Round4 路径多个出口,还带环
///////////////////////////////////////////////////////////
// 带环,有可能更小的路径被以前的路径堵住
// 可以标记走过的步数,k如果步数跟小,就还可以走
// 递归版本
void MazeInitShortPathWithCycle(Maze* maze)
{
    //当 cur > pre - 1时 pre->cur-
   //入口点的pre 是1  坐标是 -1,-1
   /*{ 0, 0, 2, 0, 0, 0 },*/
   /*{ 0, 0, 3, 0, 0, 0 },*/
   /*{ 0, 0, 4, 5, 6, 7 },*/
   /*{ 0, 0, 5, 0, 7, 0 },*/
   /*{ 9, 8, 6, 7, 8, 0 },*/
   /*{ 0, 0,11, 0, 0, 0 }*/
     int map[MAX_ROW][MAX_COL] =
    {
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1 },
        { 0, 0, 1, 0, 1, 0 },
        { 1, 1, 1, 1, 1, 0 },
        { 0, 0, 1, 0, 0, 0 }
    };
    int i;
    int j;
    for( i = 0; i < MAX_COL; i++ )
    {
        for( j = 0; j < MAX_COL;j++ )
        {
            maze->map[i][j] = map[i][j];
        }
    }

}
int CanStayWithCycle(Maze* maze, Point cur, Point pre)
{
    if( maze == NULL )
        return 0;
    if( cur.row > MAX_ROW -1 || cur.row > MAX_ROW - 1 || cur.row < 0 || cur.col < 0 )
        return 0;
    int cur_value;
    int pre_value;
    cur_value = maze->map[cur.row][cur.col];
    if( cur_value == 0 )
        return 0;
    //没走过的直接走
    if( cur_value == 1 )
        return 1;

    //走到这就代表cur是以前走到过的点,
    pre_value = maze->map[pre.row][pre.col];
    // cur = 7 pre = 6 没必要
    // cur = 7 pre = 5  可以走,比以前少一步
    // cur =2  pre = 3  cur是将要走的位置 ,pre是原本的位置
    if( cur_value >  pre_value + 1 )
    {
        return 1;
    }
    return 0;
}
void MarkWithCycle(Maze* maze, Point cur, Point pre)
{
    int cur_value;
    int pre_value;
    if(pre.row == -1 && pre.col == -1)
    {
        pre_value = 1;
    }
    else pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
}
void _GetShortPathWithCycle(Maze* maze, Point cur, Point pre, Point entry, PointStack* cur_path, PointStack *short_path)
{
    if(!CanStayWithCycle(maze, cur, pre))
        return;
    MarkWithCycle(maze, cur, pre);
    PointStackPush(cur_path, cur);
    if(IsExit(maze, cur, entry))
    {
        PointStackDebugPrint(cur_path, "路径");
        if( cur_path->size < short_path->size || short_path->size == 0 )
        {
            PointStackAssgin(short_path, cur_path);
        }
        PointStackPop(cur_path, NULL);
        return;
    }
    MazePrint(maze);
    sleep(1);
    Point up = cur;
    up.row -= 1;
    _GetShortPathWithCycle(maze, up, cur, entry, cur_path, short_path);
    Point right = cur;
    right.col += 1;
    _GetShortPathWithCycle(maze, right, cur, entry, cur_path, short_path);
    Point down = cur;
    down.row += 1;
    _GetShortPathWithCycle(maze, down, cur, entry, cur_path, short_path);
    Point left= cur;
    left.col -= 1;
    _GetShortPathWithCycle(maze, left, cur, entry, cur_path, short_path);
    PointStackPop(cur_path, NULL);

}
void GetShortPathWithCycle(Maze* maze,Point entry)
{
    PointStack cur_path;
    PointStack short_path;
    PointStackInit(&cur_path);
    PointStackInit(&short_path);
    Point pre = {-1, -1};
    _GetShortPathWithCycle(maze, entry, pre, entry, &cur_path, &short_path);
    PointStackDebugPrint(&short_path, "最短路径");
}
int main()
{
    Maze maze;
#ifdef CYCLE
    MazeInitShortPathWithCycle(&maze);
    MazePrint(&maze);
    Point entry  ={ 0, 2 };
    maze.map[entry.row][entry.col] = 2;
    GetShortPathWithCycle( &maze, entry);
#endif
#ifdef LOOP
    MazeInit(&maze);
    Point entry  ={ 0, 2 };
    GetPathByLoop(&maze, entry);
#endif
}





























