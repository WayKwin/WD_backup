#include<iostream>
#include<vector>
using namespace std;
void permutation(vector<int> &v,int pos)
{
  if((size_t)pos == v.size())
  {
    for(int i:v)
      cout<< i << ' ';
    cout<<endl;
    return ;
  }
  else
  {
    for(size_t  i = pos; i < v.size(); i++)
    {
      swap(v[i],v[pos]);
      permutation(v,pos+1); 
      swap(v[i],v[pos]);
    }
  }
  
}
/*
 * 122 212 
 * 
 * 
 */
void _swap(int a,int b)
{
  if(a !=b )
    swap(a,b);

}
void permutation_not_reapt(vector<int> &v,int pos)
{
  if((size_t)pos == v.size())
  {
    for(int i:v)
      cout<< i << ' ';
    cout<<endl;
    return ;
  }
  else
  {
    for(size_t  i = pos; i < v.size(); i++)
    {
      //if(v[i] != v[pos])
      //{
        _swap(v[i],v[pos]);
        permutation(v,pos+1); 
        _swap(v[i],v[pos]);
       //}
    }
  }
  
}
void permutation(vector<int> &v)
{
  int i = 0;
  permutation(v,i);
  //permutation_not_reapt(v,i);
}
int main()
{
  vector<int> v ={1,2,3};
  permutation(v);
  return 0 ;
}
