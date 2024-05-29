#pragma once

// �Ż��˿�������͸�ֵ���������
// �Ż��˶��Զ����������ʱ�����Ұָ������
// ������_finish�ı�ʱ�Զ�����󲻵��������������ܵ��µ��ڴ�й©����
// ��������������������֤
// ���������������test.cpp��

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
			// ������캯��Ŀǰ��һ�����⣬����Ŀǰ��������ʱ�޷��ܺõĽ��
			// vector<int> v(5, 2);
			// ��������ı����ǹ��캬��5��2��vector<int>����
			// ��ʵ���ϣ�����ʱ�����vector(InputIterator first, InputIterator last)
			// �������������
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
			// �������죬����x�����ݵ��õ��������칹���v
			// �ٽ�this��v�����ݽ���
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
			// ����д��һ��ѣ�����ֱ�ӽ�һ����������
			// ��Ϊ����x�Ǵ�ֵ���������ֱ�ӽ����Ϳ���
			// ��һЩ�����������v1 = v1��������ͬ�Ķ���ֵ
			// ���������Ҳ���������˾ͺ��Բ������ˡ�
			swap(x);

			//if (x._start == nullptr)
			//{
			//	// ��ֵ��������أ���Ҫ�����ͷ�ԭ�ռ�
			//	delete[] _start;
			//	_start = _finish = _endOfStorage = nullptr;
			//}
			//else if (this != &x) // ���������������ȣ�ֱ�ӷ��ء�
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
			// ���nС��size()����˵��Ҫɾ�����ݣ���֮����Ҫ�ں������
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
			// ������������������������
			if (n > capacity())
			{
				iterator tmp = new T[n];
				size_t oldSize = size();
				// ���_start��Ϊ�գ���Ҫ�Ѿ������ƶ����¿ռ�
				if (_start)
				{
					// memcpy���Զ���������ʵ������ܺõ�����
					// ���磬vector<string>�������ݣ����ֱ���ڴ濽��
					// ��������ʵ��string�ĳ�Ա������Ҳ����ָ��
					// ��������֮��Ҫ�ͷ�ԭ�ڴ�ռ䣬Ҳ����Ҫdelete[] _start
					// ����string���ͣ����������������������ָ��ָ��Ŀռ�ҲҪ�ͷ�
					// �����¿��ٵĿռ��п���������string��Ա������ָ����Ұָ��
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

			// ����������ݣ�pos�Ͳ������ã���Ҫ��¼���λ��
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

			// ����������ݣ�pos�Ͳ������ã���Ҫ��¼���λ��
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
			// �Ȱ������Ƶ�����
			while (it != pos + n - 1)
			{
				*it = *(it - n);
				--it;
			}
			// ������n��val
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
			// ������һ�����⣬����T��string���ͣ���ô�ڴ濽��ֱ�Ӹ���posλ�õ����ݺ�
			// posλ��ԭ��ָ��һ���ַ����ĵ�ַ�ͻᶪʧ������ַ����޷��ͷţ��Ƿ�ᵼ��
			// �ڴ�й©��
			// memcpy(pos, pos + 1, sizeof(T) * (end() - pos - 1));
			// ��˲�������ĸ�ֵ��ʽ
			while (pos + 1 != end())
			{
				*pos = *(pos + 1);
				++pos;
			}
			// ���--_finish�Ի������������⣬��֮��ѧ�ø��࣬����������
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
		iterator _start;       // ���ݵĿ�ʼλ��
		iterator _finish;       // ���һ�����ݵ���һ��λ��
		iterator _endOfStorage; // ���һ���洢�ռ����һ��λ��
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

		// �������
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