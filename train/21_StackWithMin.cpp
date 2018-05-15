#include<iostream>
#include<stack>
using namespace::std;
stack<int> m_data;
stack<int> m_min;
void StackWithMin_Push(int value)
{
  m_data.push(value);
  if(m_min.size() == 0 || value < m_min.top())
    m_min.push(value);
  else 
    m_min.push(m_min.top());
}
void StackWithMin_top(int * ret, int * min_value)
{
  if(m_data.size() ==  0)
  {
    return;
  }
   int to_ret = m_data.top();
   int to_min = m_min.top();
   if(ret != NULL)
     *ret = to_ret;
   if( min_value != NULL )
   {
     *min_value = to_min;
   }
   return;
}
void StackWithMin_Pop()
{
  m_data.pop();
  m_min.pop();
}
