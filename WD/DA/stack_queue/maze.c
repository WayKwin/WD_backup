 #include<stdio.h>
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
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 }
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
        printf("%d\n");
    }
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
//每次递归都嗲用这个函数
void _GETPATH(Maze* maze,Point cur,Point entry)
{
    //
    //深度优先搜索
    //1 判定cur是否是 1(能落脚)
    if(canStay(maze,cur))
    {
        return;
    }
    //2.给当前位置做一个标记( flag = 2 标志走过的路 )
    Maek(maze,cur);
    //3.如果当前点是出口,说明找到一条路,探测结束.
    if(IsEixt(maze,cur))
    {
        //找到出路
        printf("找到一条路径\n");
        return;
    }
}
    //4.如果不是出口,就按照顺时针探测四个相邻的点,递归调用函数自身,
    //递归时更新cur点
    //每次递归时 点都是下一次要走的点,这个点是否能走交给递归函数.

    //每个点应该有个rightpath 标记位 = 3;
    //当点进入0, rightpath = 2 出栈
    //每个点的 0 2 3 都不走
    //最后遍历整个迷宫 1 的点 找到路径



////////////////////////////////////////
//Round2 手动记录栈
///////////////////////////////////////
#include"stack.h"

void GetPathByLoop(Maze* maze, Point entry)
{
    //1 创建一个栈,并且初始化,这个站保存着走过的路径
     if(!CanStay(maze,entry))
     {
         return;
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




}
void GetPath(Maze* maze, Point entry)
{
    _GETPATH(maze,entry, entry);
}
