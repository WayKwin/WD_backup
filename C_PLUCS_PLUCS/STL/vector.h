#include<iostream>
#include<assert.h>
template<typename T>
class vector 
{
  public:
    vector():_frist(NULL),_finish(NULL),_endofstorage(NULL){}
    vector(const vector<T>& rhs);
    size_t size(){return _finish - _frist ;}
    T& operator= (vector<T> rhs);
    void insert(size_t pos, const T& x);
    void push_back(const T& x);
    //不应该提供此方法
    void push_front(const T&x);
    const T& back() const
    {
      return *(_finish - 1) ;
    }
    const T& operator[](size_t pos)
    {
      assert(pos < this->size());
      return *(_frist + pos);
    }
    T& back(size_t pos)
    {
      return const_cast<T>(static_cast<const T>(*this)[pos]);
    }



  
  protected:
  void expand(size_t newcapacity);
  T* _frist;
  //尾后
  T* _finish;
  T* _endofstorage;
};
template<typename T>
//还是要注意 为什么此处用引用的问题
vector<T>::vector(const vector<T>& rhs)
{
  // TODO 类型萃取 
   //基本数据类型可以这么做
  //size_t size = rhs.size();
  //memcpy(_frist,rhs._first,sizeof(T)*size);

  // new 调用的是自定义构造函数不影响的
  // 深拷贝的策略
  _frist = new T[rhs.size()];
  for(size_t i = 0; i < rhs.size(); i++)
  {
    _frist[i] =  rhs._frist[i];
  }

  _finish = _frist + rhs.size();
  _endofstorage = _frist + rhs.size();
}

template<typename T>
T& vector<T>::operator=(vector<T> rhs)
{
  swap(_frist,rhs._frist);
  swap(_finish,rhs._finish);
  swap(_endofstorage,rhs._endofstorage);
  return *this;
}




