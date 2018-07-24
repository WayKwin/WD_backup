//   ≈‰∆˜ƒ£ Ω
#include "Vector.h"
#include "List.h"

template<class T, class Container>
class Stack
{
public:
	void Push(const T& x)
	{
		_con.PushBack(x);
	}

	void Pop()
	{
		_con.PopBack();
	}

	size_t Size()
	{
		return _con.Size();
	}

	bool Empty()
	{
		return _con.Empty();
	}

	T& Top()
	{
		return _con.Back();
	}

protected:
	Container _con;
};

void TestStack()
{
	//Stack<int, Vector<int>> s1;
	Stack<int, List<int>> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);

	while (!s1.Empty())
	{
		cout<<s1.Top()<<" ";
		s1.Pop();
	}
	cout<<endl;
}