#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>
#include<string.h>
typedef int ROW;
typedef int COL;
using namespace::std;
extern char* ErrorString[4];
class Maze 
{
  public:
  Maze(vector<string> v):WallType('W'),RoadType('R'){
    EnterInput(v);
     ret_code ret;
    if(( ret = input_check() ) != sucess)
    {
      cout << ErrorString[ret] << endl;
      exit(1);
    }
    initMaze();
    initPoit();
  };
  enum ret_code 
  {
    invalid_input,
    number_range,
    number_format_error,
    maze_format_error,
    sucess,
  };
  void Print();
  private:
  //初始化地图
  void  initMaze();
  //初始化 每一个点在地图中的位置
  void  initPoit();
  //  初始化 点之间的关联
  const char WallType ;
  const char RoadType;
  // 输入尺寸
  pair<ROW,COL> map_size;
  // 保存外部点的连通
  vector<pair< pair<ROW,COL>,pair<ROW,COL> > > out_connected;
  // 内部地图
  vector<vector<int> > map;
  //保存 外面点和内部点的关联
  ::map<pair<ROW,COL >,pair<ROW,COL > >  OutToIn;


  // 以下是连通性辅助函数
  // 判断是row_line或者是col_line 
  enum dir
  {
   row_line,
   col_line,
   wrong_line
  };
  // 输入监测
  public:
  void EnterInput(vector<string> input)
  {
    Input = input; 
  }
  vector<string> Input;
  //输入监测
  ret_code input_check();
  // 检测输入
  void Print_Input();

  private:
 ret_code check_point_range(pair<ROW,COL> p1,pair<ROW,COL>p2);
 dir check_dir(pair<ROW,COL> p1,pair<ROW,COL>p2);
 ret_code sort_dir(pair<ROW,COL> &p1,pair<ROW,COL> &p2);
 pair<ROW,COL> GetInPoint(pair<ROW,COL> OutPoint);
 void set_road_at_map(pair<ROW,COL> p1);
 ret_code connected_point(pair<ROW,COL> p1,pair<ROW,COL>p2);
  public:
 ret_code connecte();
};

