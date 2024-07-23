#pragma once
#include <assert.h>
#include <vector>

namespace sjx
{
	template<typename T>
	struct less
	{
		bool operator()(const T& val1, const T& val2) const
		{
			return val1 < val2;
		}
	};
	template<typename T>
	struct greater
	{
		bool operator()(const T& val1, const T& val2) const
		{
			return val1 > val2;
		}
	};
	template<typename T, typename Container = std::vector<T>, typename Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue() {}
		template<typename InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			while (first < last)
			{
				push(*first);
				++first;
			}
		}
		bool empty() const
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& top() const
		{
			assert(!empty());
			return _con[0];
		}
		void push(const T& val)
		{
			_con.push_back(val);
			adjust_up(_con.size() - 1);
		}
		void pop()
		{
			std::swap(_con[0], _con[size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}
		void swap(priority_queue<T, Container>& other)
		{
			std::swap(_con, other._con);
		}

	private:
		void adjust_up(size_t child)
		{
			Compare comp;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				if (comp(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void adjust_down(size_t parent)
		{
			Compare comp;
			size_t child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < size() && comp(_con[child], _con[child + 1]))
				{
					++child;
				}
				if (comp(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
				}
				else
				{
					break;
				}
				parent = child;
				child = parent * 2 + 1;
			}
		}
		Container _con;
	};
}