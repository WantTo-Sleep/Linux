#pragma once

#include <deque>
namespace sjx
{
	template<typename T, typename Container = std::deque<T>>
	class queue
	{
	public:
		bool empty() const
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& front() const
		{
			return *(_con.begin());
		}
		const T& back() const
		{
			return *(_con.rbegin());
		}
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_front();
		}
		void swap(queue& other)
		{
			std::swap(_con, other._con);
		}
	private:
		Container _con;
	};
}