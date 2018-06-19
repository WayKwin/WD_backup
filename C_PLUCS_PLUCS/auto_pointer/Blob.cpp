#include<iostream>
#include<vector>
#include<memory>
template <typename T>
class Blob{
  public:
    typedef T ValueType;
    typedef typename std::vector<T>::size_type size_type;
    Blob() = default;
    Blob(std::initializer_list<T> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->size == 0;}
    void push_back(T &t);

  private:
    std::shared_ptr<std::vector<T> > data;
    void check(size_type i, const std::string &msg) const;
};

template< typename T >
void Blob<T>::check(size_type i,const std::string &msg)const 
{
  if(i >= data->size())
  {
    throw std::out_of_range(msg);
  }
}
template< typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il))
{
}
template< typename T>
void Blob<T>::push_back(T &t)
{
  data->push_back(std::move(t));
}
int main()
{
  std:: initializer_list<int> il = {1,2,3,4};
  std::vector<int> s(il);
}



