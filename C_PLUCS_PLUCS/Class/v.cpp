#include<iostream>
template<class T>
class Vector 
{
  public:
    Vector():_frist(NULL),_end(NULL),_endofstorage(NULL){}
    size_t size();
    size_t push_back();
    size_t insert();
  private:
      T* value;
      Vector<T>* _frist;
      Vector<T>* _end;
      Vector<T>* _endofstorage;
    
};
 

