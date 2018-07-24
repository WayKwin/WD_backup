#include<iostream>
template<class T>
class Vector
{
public:
	Vector()
		:_first(NULL)
		,_finish(NULL)
		,_endofstorage(NULL)
	{}

	Vector(const Vector<T>& v)
	{
		_first = new T[v.Size()];
		//memcpy(_first, v._first, sizeof(T)*v.Size());

		// 类型萃取
		// 1.内置类型+浅拷贝自定义类型(Date)
		//memcpy(tmp, _first, sizeof(T)*size);

		// 2.深拷贝自定义类型
		for (size_t i = 0; i < v.Size(); ++i)
		{
			_first[i] = v._first[i]; // operator=
		}

		_finish = _first + v.Size();
		_endofstorage = _first + v.Size();
	}

	Vector<T>& operator=(Vector<T> v)
	{
		swap(_first, v._first);
		swap(_finish, v._finish);
		swap(_endofstorage, v._endofstorage);

		return *this;
	}

	T& Back()
	{
		return *(_finish-1);
	}

	T& Front()
	{
		return *(_first);
	}

	~Vector()
	{
		if (_first)
		{
			delete[] _first;
		}

		_first = _finish = _endofstorage = NULL;
	}

	void PushBack(const T& x)
	{
		//Insert(0, x);
		if (_finish == _endofstorage)
		{
			size_t newcapacity = Capacity() == 0 ? 3 : Capacity()*2;
			Expand(newcapacity);
		}

		*_finish = x;
		++_finish;
	}

	void PopBack()
	{
		Erase(Size()-1);
	}

	void Insert(size_t pos, const T& x)
	{
		assert(pos <= Size());

		if (_finish == _endofstorage)
		{
			size_t newcapacity = Capacity() == 0 ? 3 : Capacity()*2;
			Expand(newcapacity);
		}

		T* end = _finish-1;
		while (end >= _first+pos)
		{
			*(end+1) = *end;
			--end;
		}

		//*(_first+pos) = x;
		_first[pos] = x;
		++_finish;
	}	

	void Erase(size_t pos)
	{
		assert(pos < Size());

		T* start = _first + pos;
		while (start < _finish-1)
		{
			*start = *(start+1);
			++start;
		}

		--_finish;
	}

	size_t Size() const
	{
		return _finish - _first;
	}

	size_t Capacity() const
	{
		return _endofstorage - _first;
	}

	bool Empty()
	{
		return _first == _finish;
	}

	T& operator[](size_t pos)
	{
		assert(pos < Size());

		return _first[pos];
	}

	void Reserve(size_t size);
	void Resize(size_t size, const T& value = T());

protected:
	void Expand(size_t newcapacity)
	{
		if (newcapacity > Capacity())
		{
			size_t size = Size();
			T* tmp = new T[newcapacity];
			if (_first)
			{
				// 类型萃取
				// 1.内置类型+浅拷贝自定义类型(Date)
				//memcpy(tmp, _first, sizeof(T)*size);

				// 2.深拷贝自定义类型
				for (size_t i = 0; i < size; ++i)
				{
					tmp[i] = _first[i]; // operator=
				}

				delete[] _first;
			}

			_first = tmp;
			_finish = _first + size;
			_endofstorage = _first + newcapacity;
		}
	}

protected:
	T* _first;
	T* _finish;
	T* _endofstorage;
};

//template<class T>
//void Vector<T>::PushBack(const T& x)
//{}

int TestVector()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);

	for (size_t i = 0; i < v1.Size(); ++i)
	{
		cout<<v1[i]<<" ";
	}
	cout<<endl;

	Vector<string> v2;
	v2.PushBack("111111");
	v2.PushBack("11111");
	v2.PushBack("11111");
	v2.PushBack("1111111111111111111111111111111111111111111111");
	v2.PushBack("11111");
	v2.PushBack("11111");
	v2.PushBack("11111");
	for (size_t i = 0; i < v2.Size(); ++i)
	{
		cout<<v2[i]<<" ";
	}
	cout<<endl;

	Vector<string> v3(v2);
	for (size_t i = 0; i < v3.Size(); ++i)
	{
		cout<<v3[i]<<" ";
	}
	cout<<endl;

	return 0;
}
