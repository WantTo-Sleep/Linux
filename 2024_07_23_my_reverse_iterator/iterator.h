#pragma once

namespace sjx
{
	template<typename Iterator>
	class reverse_iterator
	{
		typedef reverse_iterator<Iterator> self;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::pointer pointer;
	public:
		reverse_iterator() {}
		reverse_iterator(const Iterator& it) : _current(it) {}
		reverse_iterator(const self& other) : _current(other._current) {}

		reference operator*() const
		{
			Iterator tmp = _current;
			--tmp;
			return *tmp;
		}

		self& operator++()
		{
			--_current;
			return *this;
		}

		self& operator--()
		{
			++_current;
			return *this;
		}

		pointer operator->()
		{
			Iterator tmp = _current;
			--tmp;
			return tmp.operator->();
		}

		bool operator!=(const self& other) const
		{
			return _current != other._current;
		}
	private:
		Iterator _current;
	};
}	