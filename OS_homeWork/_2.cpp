#include<iostream>
#include<vector>
using namespace::std;
vector<int> Available;
vector<vector<int> > Max;
vector<vector<int> > Allocation;
vector<vector<int> >Need;
size_t P_number;
void InitAvailable()
{
  cout << "请输入元素种类" <<endl;
  size_t max;
  cin >> max;
  int k =1;
  while(Available.size() != max)
  {
    cout<<"请输入该类元素当前可获得数量" << endl; 
    cin >> k;
    Available.push_back(k); 
  }

}
void InitMax()
{
  size_t i = 0;
  size_t j = 0;
  for(i = 0; i < P_number; i ++)
  {
    for( j = 0; j < Available.size(); j++ )
    {
      int Rj;
      cout << "请输入第" << i + 1 << "个进程的第" << j + 1 << "资源" << endl;
      cin >>  Rj; 
      //此进程当前所需此类资源大于系统剩余资源
      while((Rj < Available[j]))
      {
       cout<< "非法输入" << endl ;
       cin >> Rj;
      }
      Max[i][j] = Rj; 
    }
  }
}
void InitAllocation()
{
  size_t i = 0;
  size_t j = 0;
  for( i = 0; i < P_number; i ++ )
  {
    for( j = 0; j < Available.size(); j++)
    {
      int Rj;
      cout << "请输入第" << i + 1 << "个进程已经分配的第" << j + 1 << "个资源"<< endl;
      cin >>  Rj; 
      //分配数量大于最大需求
      while((Rj > Max[i][j]))
      {
        cout<< "非法输入" << endl ;
        cin >> Rj;
      }
      Allocation[i][j] = Rj;
    }
  }
}
//i是此次修改的进程,j是此进程所需的资源
bool IsSafety(size_t i , size_t j, vector<int> Requesti)
{
    //此次的试探修改
    Available[j] = Available[j] - Requesti[j];
    Allocation[i][j] = Allocation[i][j] + Requesti[j];
    Need[i][j] = Need[i][j] - Requesti[j];
    vector<int> Work(Available);
    vector<bool> Finish(i+1,false);
    size_t _i = 0, _j = 0;
    size_t CanNotFishNumber  = Finish.size();
    size_t OldCanNotFishNumber = Finish.size();
    //安全监测
    while(CanNotFishNumber)
    {
      OldCanNotFishNumber = CanNotFishNumber;
      for( _i = 0; _i < P_number; _i++ )
      {
       for( _j = 0; _j < Available.size(); j++ )
       {
          if(Finish[_i] == false && Need[_i][_j] <= Work[_j])
          {
            Work[_j] = Work[_i] + Allocation[_i][_j];
            Finish[_i] = true;
            CanNotFishNumber--;
          }
       }
      }
      if(OldCanNotFishNumber == CanNotFishNumber)
      {
        cout << "系统不安全,撤回修改"<< endl;
        return false;
      }
    }
    return true;
}
void InitNeed()
{
  size_t i = 0;
  size_t j = 0;
  for( i = 0; i < P_number; i++ )
  {
    for( j = 0; j < Available.size(); j++ )
    {
      Need[i][j] = Max[i][j] - Allocation[i][j];
    }
  }
}
void start_blank()
{
  vector<int> Requesti;
  size_t i;
  size_t j;
  cout << "请输入进程号" << endl;
  cin >> i;
  while( i > P_number )
  {
    cout << "非法输入,请重新输入" << endl;
    cin >> i;
  }
  cout << "请输入第" << i  <<"进程所需资源种类" << endl;
  cin >> j;
  while( j > Available.size() )
  {
    cout << "非法输入,请重新输入" << endl;
    cin >> j;
  }
  cout << "请输入需要此类资源的个数";
  cin >> Requesti[j - 1];
  while( Requesti[j - 1] > Need[i - 1][j - 1] )
  {
    cout << "此进程最大需求为 " << Need[i -1][j] << endl;
    cout << "申请大于需求" << endl;
    cin >> Requesti[j];
  }
  while(Requesti[j - 1] > Available[j - 1])
  {
    cout << "当前系统此类资源剩余为" << Available[j- 1] << endl;
  }
  bool ret =IsSafety(i - 1, j - 1, Requesti);
  //如果不安全撤回修改
  if(ret == false)
  {
    Available[j-1] = Available[j-1] + Requesti[j-1];
    Allocation[i-1][j-1] = Allocation[i - 1][j -1] - Requesti[j -1];
    Need[i-1][j-1] = Need[i -1][j -1] + Requesti[j -1];
  }
}
int main()
{
  cout << "请输入进程个数"<<endl;
  cin >> P_number;
  InitAvailable();
  InitMax();
  InitNeed();
  start_blank();
    
}
