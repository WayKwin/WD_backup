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
  // 优先队列的重载函数
  struct cmp_small;;
  public:
  HuffmanTreeNode<W>* GetRoot();
  HuffmanTree():_root(NULL){};
  HuffmanTree(std::vector<W> &weight_vec,const W& invalid);
  HuffmanTree(std::vector<W> &weight_vec);
  void DisplayTree();
  private:
  void PreOrder(Node* _root);
  void BuiltTree();
  std::priority_queue<Node*,std::vector<Node*>,cmp_small > min_heap; 
  Node* _root;
};

template<typename W>
struct HuffmanTree<W>::cmp_small{
  bool operator()(Node* a,Node* b)
  {
    // 建堆的时候 比较 > 是小根堆
    return a->_w > b->_w;
  }
};

template<typename W>
void HuffmanTree<W>::BuiltTree()
{
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
    //将 最后一个节点出队列(可做可不做)
    min_heap.pop();
}

template<typename W>
HuffmanTreeNode<W>* HuffmanTree<W>::GetRoot()
{
  return _root;
}
template<typename  W>
HuffmanTree<W>::HuffmanTree(std::vector<W> &weight_vec,const W& invalid)
  {
    //std::priority_queue<Node*,std::vector<Node*>,std::greater<Node*> > min_heap; 
    //建立小根堆
    for(size_t i = 0; i < weight_vec.size(); i ++)
    {
      if(weight_vec[i] != invalid)
      {
        min_heap.push(new Node(weight_vec[i]));
      }
    }
    BuiltTree();
}
template<typename W>
HuffmanTree<W>::HuffmanTree(std::vector<W> &weight_vec)
{
  //建立小根堆
  for(size_t i = 0; i < weight_vec.size(); i ++)
  {
    min_heap.push(new Node(weight_vec[i]));
  }
  BuiltTree();
}
template<typename W>
void HuffmanTree<W>::PreOrder(Node* _root)
{
  if(_root == NULL)
      return;
  //if(_root->_left == NULL && _root->_right == NULL)
  std::cout << _root->_w._count << " ";
  PreOrder(_root->_left);
  PreOrder(_root->_right);
}
template<typename W>
void HuffmanTree<W>::DisplayTree()
{
  PreOrder(_root);
}

