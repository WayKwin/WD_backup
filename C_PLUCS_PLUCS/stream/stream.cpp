#include<iostream>
#include<string>
#include<unistd.h>
using namespace::std;
//IO 对象无赋值和拷贝 只能传引用 这里传入返回的是
//标准输入输出的对象
void ReadString(string&s)
{
    //使用 cin 只能读到 非空白的地方 输入 a b c d 只能读到a
    cin >>  s ;
    cout << s << endl;
    getline(cin,s);
    cout << s << endl;
}
ostream& Output(istream &input, string& s)
{
    input  >> s;
    return cout << s;
}
// 刷新缓冲区的三种方式
void threeFlushWay()
{
    ////类似printf 和sleep
    //三种刷新缓冲区的方式
    ostream& os = cout;
    os << "please enter a value: " << endl ;
    os << "please enter a value: " << flush;
    os << "please enter a value: " << ends;
    //设置每次输出都刷新缓冲区
    cout << unitbuf;
    cout << "hello world ";
    sleep(1);
    //返回正常模式
    cout << nounitbuf;
    cout << "你好,世界";
    sleep(1);
}
//关联函数
void testTie()
{
    ////在cin 时会刷新cout的缓冲区
    //// 因为cin和cout是关联的
    ////就像scanf会刷新printf缓冲区一样
    //// 我们可以使用tie函数来关联一类输入输出流,此时对输入流的任何操作都会立刻刷新输出流
    ostream *old_tie = cin.tie(NULL);//  两个操作 1.old_tie 返回cin原本关联的流(cout) 2.cin同时与nullptr关联 (不与任何流关联)
    cin.tie(&cerr);//将cin与cerr关联
    cin.tie(old_tie);//恢复cin老的关联

}
int main()
{
    //istream& i = cin;
    string s;
    //Output(i,s);
    ReadString(s);
    return 0;
}
