#include"non_local_static.cpp"
extern TheFileSystem ths;
class Dir 
{
  public:
    Dir();
    void print()
    {
      
    }

  TheFileSystem need_tfs;
    
};
int main()
{
  TheFileSystem s =  TheFileSystem::GetTFS();
  s.print();
}
