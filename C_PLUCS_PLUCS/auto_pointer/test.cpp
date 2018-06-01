#include<memory>
#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace::std;
int main()
{
  shared_ptr<int> p3 = make_shared<int>(42) ;
  shared_ptr<vector<int> > v1 = make_shared<vector<int>>(2);
  int a = 3;
  
  shared_ptr<int> p4 = (shared_ptr<int>)malloc(sizeof(int));
  shared_ptr<int> p2 = &a; 
