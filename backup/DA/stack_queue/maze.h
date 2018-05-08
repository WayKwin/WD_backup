#ifndef __MAZE_H__
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_ROW 6
#define MAX_COL 6
#define MAX_POINTSTACK 100

typedef struct Maze
{
    int map[MAX_ROW][MAX_COL] ;
}Maze;

typedef struct Point
{
    int row;
    int col;
}Point;
typedef struct PointStack
{
    Point p[MAX_POINTSTACK];
    int size;
}PointStack;

  int  CanStay(Maze* maze, Point cur);
  int  CanStayWithCycle(Maze* maze, Point cur, Point pre);
  void  GETPATH(Maze* maze,Point cur,Point entry, PointStack* cur_path, PointStack* short_path);
  void  GetPathByLoop(Maze* maze, Point entry);
  void  GetShortPath(Maze* maze,Point entry);
  void  GetShortPathWithCycle(Maze* maze,Point entry);
  int  IsExit(Maze* maze, Point cur, Point entry );
  void  Mark(Maze* maze, Point cur);
  void  MarkWithCycle(Maze* maze, Point cur, Point pre);
  void  MazeInit(Maze* maze);
  void  MazeInitShortPath(Maze* maze);
  void  MazeInitShortPathWithCycle(Maze* maze);
  void  MazePrint(const Maze* maze);
  void  PointStackAssgin(PointStack* stack_dst, PointStack* stack_src);
  void  PointStackDebugPrint(PointStack * stack, const char*msg);
  void  PointStackInit(PointStack* ps);
  void  PointStackPop(PointStack* ps,Point* p);
  void  PointStackPush(PointStack* ps,Point p);
  Point*  PointStackTop(PointStack*ps);
  void  _GetShortPathWithCycle(Maze* maze, Point cur, Point pre, Point entry, PointStack* cur_path, PointStack *short_path);
#endif
