#include<iostream>
class CMystring
{
  public:
    CMystring(char* pData = nullptr);
    CMystring(const CMystring&str);
    ~CMystring(void);
  private:
    char* m_pData;
};
CMystring& CMystring::operator=(const CMystring& str) noexcept
{
  if(this== &str)
    return *this;
  char* tmp = new char[strlen(str)+1];
  if(tmp == NULL)
    return *this;
  delete m_pData;
  m_pData=NULL;
  strcpy(m_pData,tmp);
}
