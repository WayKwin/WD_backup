#include<iostream>
#include<vector>
using namespace::std;
vector<int> Available;
vector<vector<int> > Max;
vector<int> Allocatoin;
vector<vector<int> >Need;
void InitAvailable(vector<int> &Available)
{
  cout << "请输入元素种类" <<endl;
  size_t max;
  cin >> max;
  int k =1;
  while(Available.size() != max)
  {
    cout<<"请输入该类元素当前可获得数量";
    cin >> k;
    Available.push_back(k); 
  }

}
void InitMax(vector<vector<int> > & Max)
{
  size_t i = 0;
  size_t j = 0;
  size_t P_number;
  cout << "请输入进程个数"<<endl;
  cin >> P_number;
  for(i = 0; i < P_number; i ++)
  {
    for( j = 0; j < Available.size(); j++ )
    {
      int Rj;
      cout << "请输入第" << i + 1 << "个进程的第" << j + 1 << "资源";
      cin >>  Rj; 
      //此进程当前所需此类资源大于系统剩余资源
      while((Rj < Available[j]))
      {
       cout<< "非法输入" ;
       cin >> Rj;
      }
      Max[i][j] = Rj; 
    }
  }
  
}

