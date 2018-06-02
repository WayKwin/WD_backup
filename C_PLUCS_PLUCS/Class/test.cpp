#include <vector>
using  namespace::std;
void f(vector<int>);

int main()
{
  //vector<int> v1 = 10;

  vector<int> v1(10);
  //f函数希望传入vector ,注意没用引用,所以是调用拷贝构造函数,
  //而且是explicit的,传入10不行
  //f(10);
  f(vector<int>(10));
}
