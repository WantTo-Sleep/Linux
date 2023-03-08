#include <iostream>
using namespace std;

// 函数模板

//template<typename T1, typename T2>
//T1 Add(T1 x, T2 y)
//{
//	return x + y;
//}
//
//int Add(int x, int y)
//{
//	return x + y;
//}
//
//template<class T>
//T Sub(const T& x, const T& y)
//{
//	return x - y;
//}
//
//int main()
//{
//	// 错误的代码，自动推演的模板不支持隐式类型转换
//	//cout << Sub(1, 2.2) << endl;
//	cout << Sub<int>(1, 2.2) << endl;
//
//	// 显示实例化
//	cout << Add<double, double>(1, 2) << endl;
//
//	//cout << Add(1, 2) << endl;
//	//cout << Add(3.3, 4.4) << endl;
//	//cout << Add(5, 6.6) << endl;
//	//cout << Add(7.7, 8) << endl;
//
//	return 0;
//}

// 类模板

template<class T>
class Stack
{
private:
	T* _a;
	size_t _size;
	size_t _capacity;
public:
	Stack(size_t capacity = 4)
		:_capacity(capacity)
		, _size(0)
	{
		_a = new T[_capacity];
	}
	~Stack()
	{
		delete[] _a;
		_a = nullptr;
		_size = _capacity = 0;
	}
	void Push(const T& x)
	{
		if (_capacity == _size)
		{
			T* _tmp = new T[_capacity * 2];
			for (size_t i = 0; i < _capacity; ++i)
			{
				_tmp[i] = _a[i];
			}
			_capacity *= 2;
			delete[] _a;
			_a = _tmp;
		}
		_a[_size++] = x;
	}
};

int main()
{
	// 类模板生成的模板类必须显示实例化类型
	Stack<int> st1;
	Stack<double> st2;

	st1.Push(1);
	st1.Push(2);
	st1.Push(3);
	st1.Push(4);
	st1.Push(5);

	st2.Push(1.1);
	st2.Push(2.2);
	st2.Push(3.3);
	st2.Push(4.4);
	st2.Push(5.5);

	return 0;
}