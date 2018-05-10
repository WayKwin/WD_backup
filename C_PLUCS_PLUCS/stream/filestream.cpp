#include<iostream>
#include<fstream>
#include<string>
using namespace::std;
void outfile()
{
    ofstream out;
    out.open("text");
    if( out )
    {
        out << "file out ";
        out << "file out ";
        out << "file out ";
        out << "file out ";
        out << "file out ";
        out.close();
    }
    ifstream in("text");
    string buf;
    if( in  )
    {
        while(!in.eof())
        {
            in >> buf;
        }
        in.close();
        cout << buf;
    }
}
int main()
{
    outfile();

    // 在创建文件流对象时就打开text文件
    //fstream f("text") ;
    ofstream of;
    //worong  open void 类型
    //if( of.open("text") )
  
    of.open("text");
    string s("abc");
    
    //if(of)//正确监测方法
    //cout << "open file successfully";
}
