#ifndef _JJALLOC_
#define _JJALLOC_ 
#include<new>
#include<cstddef>
#include<cstdlib>
#include<climits>
#include<istream>
namespace ASD 
{
  template<class T>
    inline T* _allcate(ptrdiff_t size,T *)
    {
      //分配内存失败后执行的函数 .参数是一个函数指针
      //这里设置0(NULL)表示不处理直接抛出异常
      std::set_new_handler(0);
      T* tmp = (T*) (::operator new((size_t)(size*sizeof(T))));
      if(tmp == 0)
      {
        std::cerr<<"out of memory"<< std::endl;
        exit(1);
      }


    }
}
#endif 
