# 泛型算法
都是与容器类型无关的,借助迭代器操作.
算法的操作对象从来都不是容器,而是迭代器
迭代器权利有多大,算法的能力就有多大
# 泛型算法为什么不能改变容器大小
## 1.改变容器大小会使迭代器失效
    泛型算法本身就是建立在迭代器上的
## 2.改变容器大小就要知道容器类型
    改变链表的大小就得修改指针
    改变数组的大小就得改变其内存空间大小
    这与泛型两个此是冲突的,