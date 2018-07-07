#include"huffmanTree.cpp"
#include<string>
#include<map>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdio.h>
// BUG  文件为空 或者文件里只有一种字符
class FileCompress
{
  //为什么还要这个结构体
  //哈希表 已经可以表示了
  // 因为 : 面向对象思想,代码可读性
struct CharInfo
{
    char _ch;
    //权重(出现频率)
    size_t _count;
    //编码 最后再转为位图
    std::string _code;
    //小根堆的建立
    CharInfo():_ch(-1),_count(0){};
    bool operator > (const CharInfo& info)
    {
      return this->_count > info._count;
    }
    // 最后只需要根节点有意义的节点 所以中间的非叶子节点的_ch无意义,就不用定义
    CharInfo operator+(const CharInfo& info)
    {
      CharInfo ret;
      ret._count = this->_count + info._count;
      return ret;
    }
    // huffman中非法值需要
    bool operator != (const CharInfo& info)
    {
      // 等会若count为0,就不进行加入树中
      return this->_count != info._count;
    }
};
  typedef HuffmanTreeNode<CharInfo> Node;
  public:
    enum e_method {zip,unzip};
    FileCompress(const char* file,e_method method=unzip) :tree(NULL),_read_sock(0)
    {
        ReadFile(file);
        _src_file = file;
        tree = new HuffmanTree<CharInfo> (_CharInfo,_Invalid);
        Node* node = tree->GetRoot();
        std::string code;
        GenerateHuffmanCode(node,code);
        DisplayHuffmanCode();
        Compress();
        Uncompress(file); 
    }
    ~FileCompress()
    {
      if(_read_sock >0)
      {
        close(_read_sock);
      }
      if(tree != NULL)
        delete tree;
    }
  protected:
    void ReadFile(const char*file);
    void GenerateHuffmanCode(Node* root,std::string& code);
    void DisplayHuffmanCode();
      bool Compress();
      bool Uncompress(const char* );
    std::string _src_file;
    std::string _dst_file;
    //类中包含vector 要在其他地方声明大小
    std::vector<CharInfo> _CharInfo;
    HuffmanTree<CharInfo>* tree;
    //前向定义的结构体还不知道类中构造函数只能定义为指针引用
    struct CharInfo _Invalid;
    int _read_sock;
    int _write_sock;
    int _padding_char_pos;
  
};
bool FileCompress::Uncompress(const char* file_name)
{
  _src_file = file_name;
  _src_file += ".yasuo";

  size_t pos = _src_file.rfind(".yasuo");
  if(pos == std::string::npos)
  {
    std::cout << "unzip unkown type" <<std::endl;
    exit(1);
  }

  close(_read_sock);
  _read_sock = open(_src_file.c_str(),O_RDONLY);
  std::cout<<_src_file << std::endl;
  char c ;
  while(read(_read_sock,&c,1) > 0)
  {
    std::cout << c;
  }
  exit(1);

  _src_file.replace(pos,std::string::npos,".unyasuo");
  
    close(_write_sock);
   _write_sock = open(_src_file.c_str(),O_WRONLY|O_CREAT);
   //std::cout<<_src_file <<std::endl;
   

  Node* root = tree->GetRoot(); 
  //tree->DisplayTree();
  if(root ->_left == NULL && root->_right == NULL)
  {
    // 一个字符情况下可以确定写多少个字符 不用考虑padding问题
    size_t count = 0;
    while(count != root->_w._count)
    {
      write(_write_sock,&root->_w._ch,1);
    }
  }
  else 
  {
    Node* cur = root;
    char c = 0;
    pos = 0;
    int write_end_pos  = 8;
      while(read(_read_sock,&c,1) > 0)
      {
          printf("%c\n",c);
        //std::cout<<'[' <<c<<']';
        //单独处理最后一个字符
        //if(recv(_read_sock,&c,1,MSG_PEEK) < 0)
        //{
          //write_end_pos = _padding_char_pos != 0? _padding_char_pos: write_end_pos;
        //}
        for(int i = 0; i < write_end_pos; i++)
        {
          if( (c&(1 << i) )==  0)
          {
            //std::cout << 0 << " ";
            cur = cur ->_left;
          }
          else 
          {
            //std::cout << 1 << " ";
            cur = cur ->_right;
          }
          if(cur->_left == NULL && cur->_right == NULL)
          {
            //std::cout << "asddas"<<std::endl;
            //std::cout<<cur->_w._ch;
            //printf("%c\n",cur->_w._ch);
            write(_write_sock,&cur->_w._ch,1);
            cur = root;
          }
        }
      }
  }


  //while()


  return true;
}
bool FileCompress::Compress()
{
  std::string outputfile = _src_file + ".yasuo";
  _write_sock = open(outputfile.c_str(),O_WRONLY|O_CREAT|O_APPEND);
  std::cout<<outputfile<<std::endl;
  lseek(_read_sock,0,SEEK_SET);
  char c = ' ';
  size_t pos = 0;
  size_t index = 0;
  char InputChar= 0;
  while(read(_read_sock,&c,1) > 0)
  {
    if(c == ' ')
    {
      continue;
    }
    std::string& code = _CharInfo[c]._code;
    //std::cout<<code;
    for(index = 0; index < code.size(); index++)
    {
      //int temp = pos;
      if(code[index] == '1')
      {
          InputChar |= (1<<pos++);
          //std::cout<< ( (InputChar & (0x1 <<temp )) == 0? 0:1  )<< " ";
      }
      else 
      {
          InputChar &= ~(1<<pos++);
          //std::cout<< ( (InputChar & (0x1 <<temp )) == 0? 0:1  )<< " ";
      }
      if(pos == 8)
      {
        //std::cout<<(int)'a'<<std::endl;
        //std::cout << (int)InputChar << std::endl;
        printf("%c\n",InputChar);

        write(_write_sock,&InputChar,1);       

        pos = 0;
      }
    }
  }
  if(pos != 0)
  {
    _padding_char_pos = pos;
    while(pos != 8)
    {
      InputChar |= (1<<pos++);
    }
    //int left_pos  = 8 - pos;
    //std::cout<< '[' << c <<']';
    printf("%c\n",InputChar);
    write(_write_sock,&InputChar,1);
  }
  else 
  {
    _padding_char_pos = 0;
  }
  return true;
}

void FileCompress::DisplayHuffmanCode()
{
  int i = 0;
  for(;(size_t)i < _CharInfo.size(); i++)
  {
    if(_CharInfo[i]._count != 0)
    {
      std::cout << "字符: " <<  _CharInfo[i]._ch
                << "编码" << _CharInfo[i]._code
                 << std::endl;
    }
  }
}
void FileCompress::GenerateHuffmanCode(Node* root,std::string& code)
{
   if(root == NULL)
   {
     code.pop_back();
     return;
   }
   // 这样非零会多push一次 bug
   //  考虑根节点的情况, 根节点也应该赋值
   //code.push_back('0');
   if(root->_left == NULL && root->_right == NULL)
   {
     //std::cout << code ;
     if(code.empty())
     {
        code.push_back('0');
     }
     _CharInfo[root->_w._ch]._code = code;
     //std::cout <<root->_w._ch << std::endl;
     code.pop_back();
     // 没有考虑根节点的情况
     return;
   }
   //BUG 1 根节点没有考虑进去 (一个字符的情况)
   code.push_back('0');
   GenerateHuffmanCode(root->_left,code);
   code.push_back('1');
   GenerateHuffmanCode(root->_right,code);
}
void FileCompress::ReadFile(const char* file)
{
      _CharInfo.resize(256);
       _read_sock = open(file,O_RDONLY);
      if(_read_sock < 0)
      {
        //TODO
        std::cout<< " sock < 0" << std::endl;
      }
      char c = ' ';
      //_CharInfo.resize(256);
      if(read(_read_sock,&c,1) == 0)
      {
          close(_read_sock);
          std::cout << "empty file" <<std::endl;
          exit(1);
      }
       
      lseek(_read_sock,0,SEEK_SET);
      while(read(_read_sock,&c,1) > 0)
      {
#ifdef __DEBUG__
        //std::cout<< '[' << (int)c << ']';
        //std::cout<< std::endl;
#endif
        if(c == '\n')
          continue;
        _CharInfo[c]._ch = c;
        _CharInfo[c]._count++;       
      }
      _Invalid._count = 0; 
}
int main()
{
  FileCompress test1("./file.txt");
  //std::cout << hmt._root->_w << std::endl;
  
}
