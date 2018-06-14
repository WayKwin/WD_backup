#include<iostream>
#include<vector>
#include<memory>
template <typename T> class Blob{
  public:
    typedef T ValueType;
    typedef typename std::vector<T>::size_type size_type;
    Blob() = default;
    Blob(std::initializer_list<T> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->size == 0;}

  private:
    std::shared_ptr<std::vector<T> > data;
    void check(size_type i, const std::string &msg) const;
};
