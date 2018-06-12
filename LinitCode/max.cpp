#include<iostream>
#include<string>
#include<vector>
using namespace ::std;
void swap(int  &a,int &b)
{
          int tmp = a;
                  a = b;
                          b = tmp;
                              
}
    string GetP(vector<int> &numbers,int p ,vector<string> &tmp_s)
{
         if( p == numbers.size() )
         {
                      //转化字符串
                                 int i = 0;
                                            string s;
                                                       for(; i < numbers.size(); i ++)
                                                                  {
                                                                                 s.append(i);
                                                                                            }
                                                                                                       tmp_s.push_back(s);
                                                                                                              }
                                                                                                                      
                                                                                                                              else 
                                                                                                                                      {
                                                                                                                                                  int i;
                                                                                                                                                              for(i=p; i < numbers.size(); i++)
                                                                                                                                                                          {
                                                                                                                                                                                          swap(i,p);
                                                                                                                                                                                                          GetP(numbers,p + 1);
                                                                                                                                                                                                                          swap(i,p);
                                                                                                                                                                                                                                      }
                                                                                                                                                                                                                                              }
                                                                                                                                                                                                                                                  }
                                                                                                                                                                                                                                                      string PrintMinNumber(vector<int> numbers) {
                                                                                                                                                                                                                                                              int p = 0;
                                                                                                                                                                                                                                                                      vector<string> tmp;
                                                                                                                                                                                                                                                                              GetP(numbers,p,tmp);
                                                                                                                                                                                                                                                                                      int i = 1;
                                                                                                                                                                                                                                                                                              string Max = tmp[0];
                                                                                                                                                                                                                                                                                                      for( ; i < tmp.size(); i ++ )
                                                                                                                                                                                                                                                                                                              {
                                                                                                                                                                                                                                                                                                                          if(tmp[i] > Max)
                                                                                                                                                                                                                                                                                                                                      {
                                                                                                                                                                                                                                                                                                                                                      Max = tmp[i];
                                                                                                                                                                                                                                                                                                                                                                  }
                                                                                                                                                                                                                                                                                                                                                                          }
                                                                                                                                                                                                                                                                                                                                                                                 return Max;
                                                                                                                                                                                                                                                                                                                                                                                     }
                                                                                                                                                                                                                                                                                                                                      }
                                                                                                                                                                                                                                                                                                              }
                                                                                                                                                                                                                                                      }
                                                                                                                                                                          }
                                                                                                                                      }
                                                                  }
         }
}

