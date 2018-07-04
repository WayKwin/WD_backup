#include"huffmanTree.cpp"
#include<string>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
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
  public:
    FileCompress(const char* file) :tree(NULL),_sock(0)
    {
    
       _sock = open(file,O_RDONLY);
      if(_sock < 0)
      {
        //todo
      }
      char c = ' ';
      _CharInfo.resize(256);
      while(read(_sock,&c,1) > 0)
      {
#ifdef __DEBUG__
        std::cout<< '[' << (int)c << ']';
        std::cout<< std::endl;
#endif
        _CharInfo[c]._ch = c;
        _CharInfo[c]._count++;           
      }
      _Invalid._count = 0; 
      tree = new HuffmanTree<CharInfo> (_CharInfo,_Invalid);
      //统计字母出现频率 (计数排序 数组下表)
      //std::vector<char>(256);
      //将频率构建huffman数
      //从头开始 遍历 左节点为0,右子节点为1 (0,1如何存储)
      //遍历到叶子节点 查看其权值,确定该字母的路径 (路径即huffman 编码) 使用bitmap存储?
    }
    ~FileCompress()
    {
      if(_sock >0)
      {
        close(_sock);
      }
      if(tree != NULL)
        delete tree;
    }
  protected:
    //类中包含vector 要在其他地方声明大小
    std::vector<CharInfo> _CharInfo;
    HuffmanTree<CharInfo>* tree;
    CharInfo _Invalid;
    int _sock;
};
int main()
{
  FileCompress test("./file.txt");
  //std::cout << hmt._root->_w << std::endl;
  
}
