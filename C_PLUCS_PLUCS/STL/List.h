#pragma once

template<class T>
struct ListNode
{
	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _data;

	ListNode(const T& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	List()
	{
		_head = new Node(T());
		_head->_next = _head;
		_head->_prev = _head;
	}

	// prev newnode pos
	void Insert(Node* pos, const T& x)
	{
		assert(pos);
		Node* prev = pos->_prev;
		Node* newnode = new Node(x);
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = pos;
		pos->_prev = newnode;
	}

	void Erase(Node* pos)
	{
		assert(pos && pos != _head);

		// prev pos next;
		Node* prev = pos->_prev;
		Node* next = pos->_next;

		prev->_next = next;
		next->_prev = prev;
		delete pos;
	}

	void PushBack(const T& x)
	{
		Insert(_head, x);
	}

	void PushFront(const T& x)
	{
		Insert(_head->_next, x);
	}

	void PopBack()
	{
		Erase(_head->_prev);
	}

	void PopFront()
	{
		Erase(_head->_next);
	}

	T& Back()
	{
		assert(!Empty());

		return _head->_prev->_data;
	}

	T& Front()
	{
		assert(!Empty());

		return _head->_next->_data;
	}

	size_t Size()
	{
		size_t size = 0;
		Node* cur = _head->_next;
		while (cur != _head)
		{
			++size;
			cur = cur->_next;
		}

		return size;
	}

	bool Empty()
	{
		return _head->_next == _head;
	}
protected:
	Node* _head;
};