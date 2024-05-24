#pragma once

namespace sjx
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector() :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr) {}
		vector(size_t n, const T& val = T())
		{
			reserve(n);
			for (int i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			assert(first <= last);
			while (first != last)
			{
				push_back(*(iterator)first);
				++first;
			}
		}
		vector(const vector& x)
		{
			// 拷贝构造，不需要考虑释放原空间
			if (x.capacity() != 0)
			{
				_start = new T[x.capacity()];
				memcpy(_start, x._start, sizeof(T) * x.size());
				_finish = _start + x.size();
				_endOfStorage = _start + x.capacity();
			}
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
		vector& operator=(const vector& x)
		{
			if (x._start == nullptr)
			{
				// 赋值运算符重载，需要考虑释放原空间
				delete[] _start;
				_start = _finish = _endOfStorage = nullptr;
			}
			else if (this != &x) // 如果两个操作数相等，直接返回。
			{
				delete[] _start;
				reserve(x.capacity());
				memcpy(_start, x._start, sizeof(T) * x.size());
				_finish = _start + x.size();
				_endOfStorage = _start + x.capacity();
			}
			return *this;
		}

		// Iterators:
		iterator begin()
		{
			return _start;
		}
		const_iterator begin() const
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator end() const
		{
			return _finish;
		}

		// Capacity:
		size_t size() const
		{
			return size_t(_finish - _start);
		}
		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				erase(begin() + n, end());
			}
			else
			{
				insert(end(), n - size(), val);
			}
		}
		size_t capacity() const
		{
			return size_t(_endOfStorage - _start);
		}
		bool empty() const
		{
			return begin() == end();
		}
		void reserve(size_t n)
		{
			// 新容量大于现有容量才扩容
			if (n > capacity())
			{
				iterator tmp = new T[n];
				size_t oldSize = size();
				// 如果_start不为空，需要把旧数据拷贝到新空间
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * oldSize);
					// 释放原内存空间
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + oldSize;
				_endOfStorage = _start + n;
			}
		}

		// Element access:
		T& operator[](size_t pos)
		{
			assert(pos < size());
			return *(_start + pos);
		}
		const T& operator[](size_t pos) const
		{
			assert(pos < size());
			return *(_start + pos);
		}

		// Modifiers:
		void push_back(const T& val)
 		{
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = _start ? capacity() * 2 : 4;
				reserve(newCapacity);
			}

			*_finish = val;
			++_finish;
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
		}
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= begin() && pos <= end());
			int n = pos - begin();
			// 如果发生扩容，pos就不再适用，需要记录相对位置
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = _start ? capacity() * 2 : 4;
				reserve(newCapacity);
			}
			pos = begin() + n;
			iterator it = end();
			++_finish;
			while (it != pos)
			{
				*it = *(it - 1);
				--it;
			}
			*it = val;
			return it;
		}
		void insert(iterator pos, size_t n, const T& val)
		{
			assert(pos >= begin() && pos <= end());
			int i = pos - begin();
			// 如果发生扩容，pos就不再适用，需要记录相对位置
			if (_finish + n > _endOfStorage)
			{
				size_t newCapacity = _start ? capacity() * 2 : 4;
				reserve(newCapacity);
			}
			pos = begin() + i;

			_finish += n;
			iterator it = end() - 1;
			// 先把数据移到后面
			while (it != pos + n - 1)
			{
				*it = *(it - n);
				--it;
			}
			// 再填入n个val
			while (it >= pos)
			{
				*it = val;
				--it;
			}
		}
		iterator erase(iterator pos)
		{
			assert(pos >= begin() && pos < end());
			iterator old_pos = pos;
			// 这里有一个问题，假如T是string类型，那么内存拷贝直接覆盖pos位置的数据后
			// pos位置原来指向一块字符串的地址就会丢失，这块字符串无法释放，是否会导致
			// 内存泄漏？
			// memcpy(pos, pos + 1, sizeof(T) * (end() - pos - 1));
			// 因此采用下面的赋值方式
			while (pos + 1 != end())
			{
				*pos = *(pos + 1);
				++pos;
			}
			// 这个--_finish仍会有上述的问题，待之后学得更多，回来再讨论
			--_finish;
			return old_pos;
		}
		iterator erase(iterator first, iterator last)
		{
			assert(first >= begin() && first < end());
			assert(last >= begin() && last <= end());
			assert(first <= last);

			int i = 0;
			for (; last != end(); ++i)
			{
				*(first + i) = *last;
				++last;
			}
			_finish = first + i;
			return first;
		}

	private:
		iterator _start; // 数据的开始位置
		iterator _finish; // 最后一个数据的下一个位置
		iterator _endOfStorage; // 最后一个存储空间的下一个位置
	};
	template<class T>
	ostream& operator<<(ostream& out, const vector<T>& v)
	{
		/*for (size_t i = 0; i < v.size(); ++i)
		{
			out << v[i] << ' ';
		}*/

		//auto it = v.begin();
		//while (it != v.cend())
		//{
		//	out << *it << ' ';
		//	++it;
		//}

		for (auto e : v)
		{
			out << e << ' ';
		}
		return out;
	}

	void test6()
	{
		vector<int> v1;
		v1.push_back(1);
		//v1.pop_back();
		v1.pop_back();

		//v1.push_back(2);
		//v1.push_back(3);
		//v1.push_back(4);
		//v1.push_back(5);
		//v1.push_back(6);
		//v1.push_back(7);

		//for (auto e : v1)
		//{
		//	cout << e << ' ';
		//}
		//cout << endl;

		//vector<int>::iterator it1 = v1.begin();
		//v1.insert(it1 + 7, 3, 10);
		//cout << v1 << endl;

		//v1.resize(0, 1);
		//cout << v1 << endl;

		//v1.resize(5, 5);
		//cout << v1 << endl;

		//v1.insert(it1, 2);
		//cout << v1 << endl;

		//vector<int>::iterator it1 = v1.begin();
		//vector<int>::iterator it2 = v1.end() - 7;
		//v1.erase(it1, it2);
		////v1.erase(v1.erase(it));
		//for (auto e : v1)
		//{
		//	cout << e << ' ';
		//}
		//cout << endl;
	}

	//void test1()
	//{
	//	vector<int> v1;
	//	v1.push_back(1);
	//	v1.push_back(2);
	//	v1.push_back(3);
	//	v1.push_back(4);
	//	v1.push_back(5);

	//	for (auto e : v1)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	for (auto& e : v1)
	//	{
	//		++e;
	//	}

	//	for (auto e : v1)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;

	//	vector<int> v2(v1.begin(), v1.end());
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}
	//	vector<int> v3(v1.begin() + 1, v1.end() - 1);
	//	for (auto e : v3)
	//	{
	//		cout << e << ' ';
	//	}
	//}
	//void test2()
	//{
	//	vector<int> v1(5, 2);
	//	vector<int> v2(10, 1);
	//	for (auto e : v1)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//}
	//void test3()
	//{
	//	vector<int> v1;
	//	v1.push_back(1);
	//	v1.push_back(2);
	//	v1.push_back(3);
	//	v1.push_back(4);
	//	v1.push_back(5);

	//	vector<int> v2(v1);
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	for (auto& e : v2)
	//	{
	//		++e;
	//	}
	//	vector<int> v3 = v2;
	//	for (auto e : v3)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//}
	//void test4()
	//{
	//	vector<int> v1;
	//	v1.push_back(1);
	//	v1.push_back(2);
	//	v1.push_back(3);
	//	v1.push_back(4);
	//	v1.push_back(5);

	//	vector<int> v2;
	//	v2 = v1;
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}

	//	vector<int> v3;
	//	v2 = v3;
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}

	//	v1 = v1;
	//}
	//void test5()
	//{
	//	vector<int> v1;
	//	v1.resize(10, 2);
	//	cout << v1 << endl;
	//	v1.resize(3, 3);
	//	cout << v1 << endl;
	//	v1.resize(10, 3);
	//	cout << v1 << endl;

	//}
}