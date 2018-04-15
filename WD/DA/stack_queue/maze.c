 #include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_ROW 6
#define MAX_COL 6

typedef struct Maze
{
    int map[MAX_ROW][MAX_COL] ;
}Maze;
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
typedef struct Point
{
    int row;
    int col;
}Point;
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
int   _GETPATH(Maze* maze,Point cur,Point entry)
{
    int flag = 0;
        //就像最长子序列 ,递归无法获得轨迹
        //因为返回值就一个
      // n-1 只能获得 n的一个状态(之后会被覆盖)
        //实际上是把能走1的都走完,是一种遍历
    if(!CanStay(maze,cur))
    {
        return  0;
    }

    Mark(maze,cur);

    if(IsExit(maze,cur,entry))
    {
        maze->map[cur.row][cur.col] = 2;

        printf("找到一条路径\n");
        return 1;
    }

     Point p;
     p.row = cur.row - 1;
     p.col = cur.col;
     _GETPATH(maze, p, entry);

     flag = _GETPATH(maze, p, entry);

     p.row = cur.row;
     p.col = cur.col + 1;

     flag = _GETPATH(maze, p, entry);

     p.row = cur.row + 1;
     p.col = cur.col ;
     flag = _GETPATH(maze, p, entry);

     p.row = cur.row;
     p.col = cur.col - 1;
     flag = _GETPATH(maze, p, entry);

     return 0;

}

////////////////////////////////////////
//Round2 手动记录栈
///////////////////////////////////////
/*#ifdef Round2*/
#define MAX_POINTSTACK 100
typedef struct PointStack
{
    Point p[MAX_POINTSTACK];
    int size;
}PointStack;
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

PointStack ps;
void GetPathByLoop(Maze* maze, Point entry)
{
    PointStackInit(&ps);
    Point p = entry;
    PointStackPush(&ps,p);
    while(PointStackTop(&ps) != NULL)
    {
        if(IsExit(maze,p,entry))
        {
            break;
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
    //while(canstay ) 遇到exit  循环出栈打印到空,然后继续continue
    /*while(1)*/
    /*{*/
        /*if( (p.row -= 1,  CanStay(maze,p) ))*/
        /*{*/
            /*Mark(maze,p);*/
            /*PointStackPush(&ps,p);*/
            /*continue;*/
        /*}*/
        /*else*/
        /*{*/
            /*p.row += 1;*/
        /*}*/
        /*if(( p.col += 1 , CanStay(maze,p) ))*/
        /*{*/
            /*Mark(maze,p);*/
            /*PointStackPush(&ps,p);*/
            /*continue;*/
        /*}*/
        /*else*/
        /*{*/
            /*p.col -= 1;*/
        /*}*/
        /*if((p.row += 1, CanStay(maze,p)))*/
        /*{*/
            /*Mark(maze,p);*/
            /*PointStackPush(&ps,p);*/
            /*continue;*/
        /*}*/
        /*else*/
        /*{*/
            /*p.row -= 1;*/
        /*}*/


        /*if(( p.col -= 1 , CanStay(maze,p) ))*/
        /*{*/
            /*Mark(maze,p);*/
            /*PointStackPush(&ps,p);*/
            /*continue;*/
         /*}*/
        /*else*/
        /*{*/
            /*p.col += 1;*/
        /*}*/
        /*if( PointStackTop(&ps) == NULL)*/
        /*{*/
            /*break;*/
        /*}*/
        /*if(IsExit(maze,*PointStackTop(&ps),p))*/
        /*{*/
            /*break;*/
        /*}*/
        /*PointStackPop(&ps,NULL);*/
     /*}*/
    MazePrint(maze);
    Point* ret ;
    printf("一条路径为: ");
    while(( ret=PointStackTop(&ps) ) != NULL)
    {

        printf("(%d,%d) ",ret->row,ret->col);
        PointStackPop(&ps,NULL);
    }
    printf("\n");


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




}
int main()
{
    Maze maze;
    Point entry;
    entry.row = 0;
    entry.col = 2;
    MazeInit(&maze);
    MazePrint(&maze);
    GetPathByLoop(&maze,entry);
    MazePrint(&maze);
    return 0;
}
