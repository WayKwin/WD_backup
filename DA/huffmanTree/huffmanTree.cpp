#include<iostream>
//建立堆
#include<algorithm>
#include<queue>
#include<vector>
template<typename T>
struct HuffmanTreeNode 
{
  T _w;//权值 
  HuffmanTreeNode<T>* _left;
  HuffmanTreeNode<T>* _right;
  HuffmanTreeNode(T _w):_w(_w) , _left(NULL),_right(NULL){};
};
template<typename W>
    //内部类 class 修饰,外部不能访问内部 相当于一个private  的变量
class HuffmanTree 
{
  typedef HuffmanTreeNode<W> Node;
  struct cmp_small{
    bool operator()(Node* a,Node* b)
    {
      // 建堆的时候 比较 > 是小根堆
      return a->_w > b->_w;
    }
};
  public:
  HuffmanTree():_root(NULL){};
  HuffmanTree(std::vector<W> &weight_vec,const W& invalid)
  {
    std::priority_queue<Node*,std::vector<Node*>,cmp_small> min_heap; 
    
    //建立小根堆
    for(size_t i = 0; i < weight_vec.size(); i ++)
    {
      if(weight_vec[i] != invalid)
      {
#ifdef __DEBUG__
        std::cout<<'['<< weight_vec[i]._ch << '|' <<  weight_vec[i]._count << ']' << ' ';
#endif
        min_heap.push(new Node(weight_vec[i]));
      }
    }

#ifdef __DEBUG__
    std::cout<< min_heap.top()->_w._count;
#endif

    // >1 最后一个循环是 两个节点 分别是left和right  然后建立了parent(root) 
    while(min_heap.size() > 1)
    {
#ifdef __DEBUG__
        std::cout<< min_heap.top()->_w._count;
#endif
      Node* left = min_heap.top();
      min_heap.pop();
      Node* right = min_heap.top();
      min_heap.pop();
      Node* parent = new Node(left->_w +right->_w);
      min_heap.push(parent);
      parent->_left = left;
      parent->_right = right;
    }
    // 根节点
    _root = min_heap.top();
#ifdef __DEBUG__
    std::cout << "root:" <<  _root->_w._count << std::endl;
#endif
    min_heap.pop();

  }
  HuffmanTree(std::vector<W> &weight_vec)
  {
    // 通过W 权值构建Node 的 优先队列( 因为Node 和Node 要组成huffman 树)
    std::priority_queue<Node*,std::vector<Node*>,std::greater<Node*> > min_heap; 
    
    //建立小根堆
    for(size_t i = 0; i < weight_vec.size(); i ++)
    {
      min_heap.push(new Node(weight_vec[i]));
    }

    // >1 最后一个循环是 两个节点 分别是left和right  然后建立了parent(root) 
    while(min_heap.size() > 1)
    {
      Node* left = min_heap.top();
      min_heap.pop();
      Node* right = min_heap.top();
      min_heap.pop();
      Node* parent = new Node(left->_w +right->_w);
      min_heap.push(parent);
      parent->_left = left;
      parent->_right = right;
    }
    // 根节点
    _root = min_heap.top();
    min_heap.pop();
  }
  public:

  Node* _root;
};
struct cmp_small {
  bool operator()(int a,int b)
  {
    return a < b;
  }
};
