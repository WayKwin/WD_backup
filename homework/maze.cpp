#include"maze.h"
char* ErrorString[] = {
  "Invalid number format.",
  "Number out of range.",
  "Incorrect command format.",
  "Maze format error."
};

Maze::ret_code Maze::input_check()
{  
  if(Input.size() > 2)
  {
    printf("%s %d\n",__FUNCTION__,__LINE__);
    return number_format_error; 
  }
  int row,col; 
  string frist_line = Input[0];
  if(sscanf(frist_line.c_str(),"%d,%d",&row,&col) != 2)
  {
    // 格式不符
    //printf("%s %d\n",__FUNCTION__,__LINE__);
    return  number_format_error;
  }

  if(row < 0 || col < 0)
    return invalid_input;
  map_size.first = row;
  map_size.second = col;

  string second_line = Input[1]; 

  int pos = second_line.find(';');
  int begin = 0;
  int num1,num2,num3,num4;
  while(pos !=string::npos)
  {

    string block(second_line,begin,pos); 
    //printf("loop: %d\n",pos);
    //printf("不符合的字符串是 :%s\n",block.c_str());
    if(sscanf(block.c_str(),"%d,%d %d,%d",&num1,&num2,&num3,&num4) !=4)
    {
      auto i = block.begin();
      //printf("不符合的字符串是 :%s\n",block.c_str());
      for(; i < block.end(); i++)
      {
        if(( *i < '0' || *i > '9' ) && *i != ',')
        {
          return invalid_input;
        }
      }
      //printf("%s %d\n",__FUNCTION__,__LINE__);
      return number_format_error;
    }
    pair<ROW,COL> p1;
    p1.first = num1;
    p1.second= num2;
    pair<ROW,COL> p2;
    p2.first = num3;
    p2.second= num4;
  
    if(check_point_range(p1,p2) != sucess)
    {
      //printf("%s %d\n",__FUNCTION__,__LINE__);
       return number_range;
    }
    pair<pair<ROW,COL>,pair<ROW,COL> > elem;
    elem.first = p1;
    elem.second = p2;
    out_connected.push_back(elem);

    if(pos == second_line.size())
      return number_format_error;
    pos+=1;
    if(pos == second_line.size())
      return number_format_error;
    begin = pos;
    pos = second_line.find(';',pos);
  }
  //退出循环 begin 指向最后 一对 点坐标
  string block(second_line,begin,second_line.size()); 
  if(block.size() != 7)
    return number_format_error;
  if(sscanf(block.c_str(),"%d,%d %d,%d",&num1,&num2,&num3,&num4) !=4)
  {
#if 0
    printf("不符合的字符串是 :%s\n",block.c_str());
    printf("%s %d\n",__FUNCTION__,__LINE__);
#endif
    return number_format_error;
  }
  pair<ROW,COL> p1;
  p1.first = num1;
  p1.second= num2;
  pair<ROW,COL> p2;
  p2.first = num3;
  p2.second= num4;

  if(check_point_range(p1,p2) != sucess)
  {
    //printf("%s %d\n",__FUNCTION__,__LINE__);
     return number_range;
  }
  pair<pair<ROW,COL>,pair<ROW,COL> > elem;
  elem.first = p1;
  elem.second = p2;
  out_connected.push_back(elem);
  
  return sucess;
}
void Maze::Print_Input()
{
    
    for(auto i : out_connected)
    {
      printf("{%d,%d},{%d,%d}",
            i.first.first,
            i.first.second,
            i.second.first,
            i.second.second
          );
    }
}
Maze::ret_code Maze::check_point_range(pair<ROW,COL> p1,pair<ROW,COL>p2)
  {
    if(p1.first >= map_size.first || p1.first < 0 || p2.second >= map_size.second || p2.second < 0  )
    {
      //printf("%s(): %d error",__FUNCTION__,__LINE__);
      return number_range;
    }
    return sucess;
  }
Maze::dir Maze::check_dir(pair<ROW,COL> p1,pair<ROW,COL>p2)
  {
    // 判断两个点的方向
    if(p1.first == p2.first && p1.second != p2.second)
      return col_line;
    else if(p1.first != p2.first && p1.second == p2.second)
      return row_line;
    //else if(p1.first != p2.first && p1.first != p2.second)
    else 
    {
      //printf("%s(): %d error",__FUNCTION__,__LINE__);
      return wrong_line;
    }
  };
Maze::ret_code Maze::sort_dir(pair<ROW,COL> &p1,pair<ROW,COL> &p2)
  {
    Maze::dir ret = check_dir(p1,p2);
    if(ret == row_line)
    {
      if(p1.first> p2.first)
      {
        swap(p1.first,p2.first);
        //  两个点不相邻 的错误
        if(p2.first - p1.first> 1 )
        {
          //printf("%s(): %d error",__FUNCTION__,__LINE__);
          return maze_format_error;  
        }
      }
    }
    else if(ret == col_line)
    {
      if(p1.second> p2.second)
      {
        swap(p1.second, p2.second);
        //不相邻
        //区分不相邻和对角线
        if(p2.second- p1.second > 1 )
        {
#if 0
          printf("p2.second: %d p1.second :%d\n",p2.second,p1.second);
            printf("%s(): %d format_error",__FUNCTION__,__LINE__);
#endif
          return maze_format_error;  
        }
      }
    }
    else 
    {
      //对角线
    #if 0
      printf("%s(): %d invalid_error\n",__FUNCTION__,__LINE__);
      printf("p2.first: %d p1.first :%d\n",p2.first,p1.first);
      printf("p2.second: %d p1.second :%d\n",p2.second,p1.second);
#endif
      return  maze_format_error;  
    }
    return sucess;
  }
 pair<ROW,COL> Maze::GetInPoint(pair<ROW,COL> OutPoint)
 {
   auto iter = OutToIn.find(OutPoint) ;
   if(iter == OutToIn.end())
     return {-1,-1};
   else 
     //printf("%d, %d\n",iter->second.first,iter->second.second);
     return iter->second;
 }
 void Maze::set_road_at_map(pair<ROW,COL> p1)
 {
    map[p1.first][p1.second] = 1;
 }
Maze::ret_code Maze::connected_point(pair<ROW,COL> p1,pair<ROW,COL>p2)
 {
    ret_code ret;
    if((ret = sort_dir(p1,p2)) != sucess)
    {
      return ret;
    }
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
Maze::ret_code Maze::connecte()
 {
   ret_code ret;
    auto iter = out_connected.begin();
    for(; iter != out_connected.end(); iter++)
    {
      if(( ret= connected_point(iter->first,iter->second) ) != sucess) 
      {
        cout << ErrorString[ret] << endl;
        exit(1);
      }
    }
    return sucess;
 }
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
