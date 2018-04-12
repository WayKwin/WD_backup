#include"tree.h"
int main()
{
   BST tree;
    tree.put('a',1);
    tree.put('e',1);
    tree.put('f',1);
    tree.put('g',1);
    tree.put('h',1);
    tree.put('b',1);
    tree.put('c',1);
    tree.put('d',1);
    //tree.deleteMin();
    //tree.deleteMin();
    //tree.deleteMin();
    //tree.deleteMin();
    //tree.deleteMin();
    //tree.deleteMin();
    //tree.deleteMin();
    //tree.deleteMin();
    tree.deleteNode('d');
    tree.deleteNode('e');
    tree.deleteNode('f');
    tree.deleteNode('a');
    tree.deleteNode('b');
    tree.deleteNode('c');
    tree.deleteNode('g');
    tree.deleteNode('h');
    std::cout<<tree.isEmpty()<<std::endl;
    return 0;
}
