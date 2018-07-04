#include<iostream>
#include<queue>
#define N 5
using namespace std;
//邻接矩阵
int maze[N][N] = {
       //a  b  c  d  e   
 /*a*/ { 0, 1, 1, 0, 0  },
 /*b*/ { 0, 0, 1, 1, 0  },
 /*c*/ { 0, 1, 1, 1, 0  },
 /*d*/ { 1, 0, 0, 0, 0  },
 /*e*/ { 0, 0, 1, 1, 0  }
};
// 从a开始, 初始化队列queue
// push a < a > 
// 取front:a  visited b=1 c=1       push b c  pop a  访问结果:[ a ]       队列情况< b c >
// 取front:b  visited c=1 d=1       push d    pop b  访问结果:[ a b ]     队列情况< c d >  
// 取front:c  visited b=1 c=1 d=1   push NULL pop c  访问结果:[ a b c ]   队列情况< d   >
// 取fonnt:d  visited a=1           push NULL pop d  访问结果:[ a b c d ] 队列情况<empty>  
// 所以从a出发每次广度遍历,发现e对于a是不可达的
// 所以出发点要依次从 a b c d e 开始 保证访问不可达的点
int visited[N]  = {0};
void BFS(int entery)
{
  queue<int> Q;
  Q.push(entery);
  visited[entery] = 1;
  while(!Q.empty())
  {
    int front = Q.front();
    Q.pop();
    cout << front + 1;
    int i  = 0;
    for(i = 0; i < N ; i++ )
    {
      //                     从front开始遍历
      if(!visited[i] && maze[front][i] == 1)
      {
        visited[i] = 1;
        Q.push(i);
      }
    }
  }
}
int main()
{
  int i ;
  //从每个节点作为出发点
  for(i = 0; i < N; i++)
  {
    if(visited[i] != 1 )
    {
      BFS(i); 
    }
  }
}
