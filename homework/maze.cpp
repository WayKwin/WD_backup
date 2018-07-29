#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>
#include<sstream>

typedef int ROW;
typedef int COL;
using namespace::std;
class Maze 
{
  public:
  Maze(pair<int,int> size):WallType('W'),RoadType('R'),map_size(size)
  {
    initMaze();
    initPoit();
  };
  void Create();
  void Print();
  private:
  bool Check();
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
  //unordered_map<pair<ROW,COL >,pair<ROW,COL > >  OutToIn;
  ::map<pair<ROW,COL >,pair<ROW,COL > >  OutToIn;


  // 以下是连通性辅助函数
  // 判断是row_line或者是col_line 
  enum dir
  {
   row_line,
   col_line,
   wrong_line
  };
  public:
  enum ret_code 
  {
    sucess,
    invalid_input,
    repeat_input,
    format_error,
    number_range,
  };
  private:
  ret_code check_poit_range(pair<ROW,COL> p1,pair<ROW,COL>p2)
  {
    if(p1.first >= map_size.first || p1.first < 0 || p2.second >= map_size.second || p2.second < 0  )
    {
      printf("%s(): %d error",__FUNCTION__,__LINE__);
      return number_range;
    }
    return sucess;
  }
  dir check_dir(pair<ROW,COL> p1,pair<ROW,COL>p2)
  {
    if(p1.first == p2.first && p1.second != p2.second)
      return col_line;
    else if(p1.first != p2.first && p1.second == p2.second)
      return row_line;
    //else if(p1.first != p2.first && p1.first != p2.second)
    else 
    {
      printf("%s(): %d error",__FUNCTION__,__LINE__);
      return wrong_line;
    }
  };
 ret_code sort_dir(pair<ROW,COL> &p1,pair<ROW,COL> &p2)
  {
    dir ret = check_dir(p1,p2);
    if(ret == row_line)
    {
      if(p1.first> p2.first)
      {
        swap(p1.first,p2.first);
        //  两个点不相邻
        if(p2.first - p1.first> 1 )
        {
          printf("%s(): %d error",__FUNCTION__,__LINE__);
          return format_error;  
        }
      }
    }
    else if(ret == col_line)
    {
      if(p1.second> p2.second)
      {
        swap(p1.second, p2.second);
        if(p2.second- p1.second > 1 )
        {
          printf("p2.second: %d p1.second :%d\n",p2.second,p1.second);
          printf("%s(): %d format_error",__FUNCTION__,__LINE__);
          return format_error;  
        }
      }
    }
    else 
    {
      printf("%s(): %d invalid_error\n",__FUNCTION__,__LINE__);
      printf("p2.first: %d p1.first :%d\n",p2.first,p1.first);
      printf("p2.second: %d p1.second :%d\n",p2.second,p1.second);
      return  invalid_input;  
    }
    return sucess;
  }
 pair<ROW,COL> GetInPoint(pair<ROW,COL> OutPoint)
 {
   auto iter = OutToIn.find(OutPoint) ;
   if(iter == OutToIn.end())
     return {-1,-1};
   else 
     //printf("%d, %d\n",iter->second.first,iter->second.second);
     return iter->second;
 }
 void set_road_at_map(pair<ROW,COL> p1)
 {
    map[p1.first][p1.second] = 1;
 }
 ret_code connected_point(pair<ROW,COL> p1,pair<ROW,COL>p2)
 {
   ret_code ret;
    if(( ret = check_poit_range(p1,p2) ) != sucess)
    {
      return ret;
    }
    if((ret = sort_dir(p1,p2)) != sucess)
      return ret;
    pair <ROW,COL> in_point;
    in_point = GetInPoint(p1);
    // 行不同
    if(check_dir(p1,p2) == row_line)
    {
      in_point.first += 1;
    }
    // 列不同
    else if(check_dir(p1,p2) == col_line)
    {
      in_point.second+= 1;
    }
    if(in_point.first == -1 || in_point.second == -1)
    {
      printf("p1.frist: %d p1.second:%d\n",p1.first,p1.second);
      return invalid_input;
    }
    //printf("%d\n",in_point.second);

    set_road_at_map(in_point);
    return sucess; 
 }
  public:
 //string Render()
 //{

 //}
 ret_code connecte(vector<pair< pair<ROW,COL>,pair<ROW,COL> > > out_connected)
 {
    auto iter = out_connected.begin();
    ret_code ret;
    for(; iter != out_connected.end(); iter++)
    {
      if(( ret= connected_point(iter->first,iter->second) ) != sucess) 
      {
        return ret;
      }
    }
    return sucess;
 }
};

void Maze::initMaze()
{
  //init row
  size_t map_row  = 2*map_size.first + 1;
  size_t map_col  = 2*map_size.second+ 1;
  map.resize(map_row);
  for(size_t i = 0; i < map_row; i++ )
  {
    map[i].resize(map_col);
  }
}
void Maze::initPoit()
{
  int col_gap = 1;
  int row_gap = 1;
  for(int i = 0; i < map_size.first;i++)
  {
    col_gap = 1;
    for(int j = 0; j < map_size.second;j++)
    {
      pair<ROW,COL> out = {i,j};
      pair<ROW,COL> in = {i+row_gap,j+col_gap};

      // 这里测试错误重复输入点 TODO
      OutToIn.insert({out,in}); 
      if(OutToIn.find(out) == OutToIn.end())
      {
        printf("eorr\n");
      }
      map[i + row_gap][j + col_gap] = 1;  
      col_gap++;
    }
    row_gap++;
  }
}
void Maze::Print()
{
  for(auto i: map)
  {
    for(auto j: i)
    {
        printf("[%c] ",j == 0? WallType: RoadType);
    }
    printf("\n");
  }
}
// TODO  代码重构
//  input command 
int main()
{
  //pair<int,int>size  = {3,3};
  //Maze m = Maze(size);
  //vector<pair< pair<ROW,COL>,pair<ROW,COL> > > out_connected;
  //out_connected = {
    ////{{1,0},{0,0}},
    //{{0,1},{0,2}},
    //{{0,0},{1,0}},
    //{{0,1},{1,1}},
    //{{0,2},{1,2}},
    //{{1,0},{1,1}},
    //{{1,1},{1,2}},
    //{{1,1},{2,1}},
    //{{1,2},{2,2}},
    //{{2,0},{2,1}},
  //};
  //Maze::ret_code ret  = m.connecte(out_connected);
  //if(ret != Maze::sucess)
  //{
    //printf("123\n");
  //}
  //m.Print();
  string s ;
  int count = 0;
  while(getline(cin,s))
  {
    //s.push_back('\n');
    count ++;
    if(count >= 2)
      break;
  }
  //cin >> s;  
  cout << s << endl;

}
