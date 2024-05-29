#pragma once

// 优化了拷贝构造和赋值运算符重载
// 优化了对自定义对象扩容时引起的野指针问题
// 考虑了_finish改变时自定义对象不调用析构函数可能导致的内存泄漏问题
// 引入杨辉三角这个题来验证
// 其余测试用例放入test.cpp中

namespace sjx
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector() :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr) {}
		vector(size_t n, const T& val = T()) :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{
			// 这个构造函数目前有一点问题，以我目前的能力暂时无法很好的解决
			// vector<int> v(5, 2);
			// 上述代码的本意是构造含有5个2的vector<int>对象
			// 但实际上，运行时会调用vector(InputIterator first, InputIterator last)
			// 这个迭代器构造
			reserve(n);
			for (int i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{
			assert(first <= last);
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(const vector& x) :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{
			// 拷贝构造，先用x的内容调用迭代器构造构造出v
			// 再将this和v的内容交换
			vector<T> v(x.begin(), x.end());
			swap(v);
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
		vector<T>& operator=(vector<T> x)
		{
			// 下面写了一大堆，不如直接叫一个打工人来打工
			// 因为参数x是传值拷贝，因此直接交换就可以
			// 有一些极少数情况：v1 = v1，两个相同的对象赋值
			// 这种情况下也不会出错，因此就忽略不讨论了。
			swap(x);

			//if (x._start == nullptr)
			//{
			//	// 赋值运算符重载，需要考虑释放原空间
			//	delete[] _start;
			//	_start = _finish = _endOfStorage = nullptr;
			//}
			//else if (this != &x) // 如果两个操作数相等，直接返回。
			//{
			//	delete[] _start;
			//	reserve(x.capacity());
			//	memcpy(_start, x._start, sizeof(T) * x.size());
			//	_finish = _start + x.size();
			//	_endOfStorage = _start + x.capacity();
			//}
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
			// 如果n小于size()，就说明要删除数据，反之，就要在后面添加
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
				// 如果_start不为空，需要把旧数据移动到新空间
				if (_start)
				{
					// memcpy对自定义类型其实并不会很好的适用
					// 例如，vector<string>类型扩容，如果直接内存拷贝
					// 拷贝的其实是string的成员变量，也就是指针
					// 但拷贝完之后要释放原内存空间，也就是要delete[] _start
					// 对于string类型，会调用它的析构函数，对指针指向的空间也要释放
					// 导致新开辟的空间中拷贝过来的string成员变量的指针变成野指针
					// memcpy(tmp, _start, sizeof(T) * oldSize);
					
					for (size_t i = 0; i < oldSize; ++i)
					{
						tmp[i] = _start[i];
					}
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
			return _start[pos];
		}
		const T& operator[](size_t pos) const
		{
			assert(pos < size());
			return _start[pos];
		}

		// Modifiers:
		void push_back(const T& val)
 		{
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);
			}

			*_finish = val;
			++_finish;
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
			(*_finish).~T();
		}
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= begin() && pos <= end());

			// 如果发生扩容，pos就不再适用，需要记录相对位置
			int n = pos - begin();
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

			// 如果发生扩容，pos就不再适用，需要记录相对位置
			int i = pos - begin();
			if (_finish + n > _endOfStorage)
			{
				size_t newCapacity = _start ? capacity() * 2 : 4;
				if (size() + n > newCapacity)
				{
					newCapacity = size() + n;
				}
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
		void swap(vector<T>& x)
		{
			std::swap(x._start, _start);
			std::swap(x._finish, _finish);
			std::swap(x._endOfStorage, _endOfStorage);
		}
		void clear()
		{
			_finish = _start;
		}

	private:
		iterator _start;       // 数据的开始位置
		iterator _finish;       // 最后一个数据的下一个位置
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

	class Solution
	{
	public:
		vector<vector<int>> generate(int numRows)
		{
			vector<vector<int>> vv;

			vv.resize(numRows);

			for (int i = 0; i < numRows; ++i)
			{
				vv[i].resize(i + 1, 1);
			}

			for (int i = 2; i < numRows; ++i)
			{
				for (int j = 1; j < i; ++j)
				{
					vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
				}
			}

			return vv;
		}
	};

	void test_vector_oj()
	{
		//vector<int> v;
		//v.push_back(1);
		//v.pop_back();

		// 杨辉三角
		vector<vector<int>> vv = Solution().generate(10);

		for (int i = 0; i < vv.size(); ++i)
		{
			for (int j = 0; j < vv[i].size(); ++j)
			{
				cout << vv[i][j] << ' ';
			}
			cout << endl;
		}

		vv.pop_back();
		vv.pop_back();
		vv.pop_back();
		vv.pop_back();
		vv.pop_back();
		vv.pop_back();

	}
}