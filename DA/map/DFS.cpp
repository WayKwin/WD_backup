#include<iostream>
#include<stack>
#define N 5
using namespace std;
//邻接矩阵
int maze[N][N] = {

       //a  b  c  d  e   
 /*a*/ { 0, 1, 1, 0, 0  },
 /*b*/ { 0, 0, 1, 0, 1  },
 /*c*/ { 0, 0, 1, 0, 0  },
 /*d*/ { 1, 1, 0, 0, 1  },
 /*e*/ { 0, 0, 1, 0, 0  }
};
// DFS 每行只要碰到1 就先往下走,走投无路就返回,然后横着直到遇到下一个1
int visited[N] = {0};
void dfs(int entery)
{
  visited[entery] = 1;
  for(int i = 0; i < N; i++)
  {
    if(visited[i] == 0 && maze[entery][i] == 1)
    {
      dfs(i);
    }
  }
  cout<< entery + 1 ;
}
void dfs_by_stack(int entery)
{
     //a  b  c  d  e   
 //a { 0, 1, 1, 0, 0  },
 //b { 0, 0, 1, 0, 1  },
 //c { 0, 0, 1, 0, 0  },
 //d { 1, 1, 0, 0, 1  },
 //e { 0, 0, 1, 0, 0  }
  stack<int> s;
  s.push(entery);
  visited[entery] = 1;
  while(!s.empty())
  {
   int v = s.top();
   bool reach_end = true;
   for(int i = 0; i < N; i++)
   {
     //找到每行第一个1就退出
     if(visited[i] == 0 && maze[v][i] == 1)
     {
       s.push(i);
       visited[i] = 1;
       reach_end = false;
       //找到一个点就结束 竖向优先
       break;
     }
   }
   if(reach_end == true)
   {
     //在递归结束时输出
      //回溯
      cout<< v + 1  ;
      s.pop();
   }
  }
}
int main()
{
  //for(int i = 0 ; i < N; i++)
  //{
     //if(visited[i] == 0)
     //{
       //dfs(i);
     //}
  //}
  cout << endl;
  for(int i = 0 ; i < N; i++)
  {
     if(visited[i] == 0)
     {
       dfs_by_stack(i);
     }
  }
}

