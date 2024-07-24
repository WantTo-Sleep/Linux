#pragma once

namespace sjx
{
	template <typename T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		__list_node(const T& val = T()) :_data(val), _next(nullptr), _prev(nullptr)
		{

		}
	};

	template <typename T, typename Ref, typename Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> node;
		typedef __list_node<T>* node_pointer;

		typedef __list_iterator<T, Ref, Ptr> self;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		typedef typename Ref reference;
		typedef typename Ptr pointer;

		node_pointer _pnode;

		__list_iterator(const node_pointer& val = nullptr) :_pnode(val) {}
		__list_iterator(const iterator& it) :_pnode(it._pnode) {}

		Ref operator*()
		{
			return _pnode->_data;
		}
		Ptr operator->()
		{
			return &(_pnode->_data);
		}
		bool operator!=(const self& val) const
		{
			return _pnode != val._pnode;
		}
		bool operator==(const self& val) const
		{
			return _pnode == val._pnode;
		}

		self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}
		self operator++(int)
		{
			self tmp(_pnode);
			_pnode = _pnode->_next;
			return tmp;
		}
		self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}
		self operator--(int)
		{
			self tmp(_pnode);
			_pnode = _pnode->_prev;
			return tmp;
		}
	};

	template<typename Iterator>
	class reverse_iterator
	{
		typedef reverse_iterator<Iterator> self;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::pointer pointer;
	public:
		reverse_iterator() {}
		reverse_iterator(const Iterator& it) : _current(it) {}
		template<typename Iter>
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

	template <typename T>
	class list
	{
	public:
		typedef __list_node<T> node;
		typedef __list_node<T>* node_pointer;

		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;


		list()
		{
			empty_initialize();
		}
		template <typename InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		list(const list& other)
		{
			empty_initialize();
			list<T> tmp(other.begin(), other.end());
			swap(tmp);
		}

		~list()
		{
			clear();
			delete _head;
		}

		list<T>& operator=(list<T> other)
		{
			empty_initialize();
			swap(other);
			return *this;
		}


		// Element access
		T& front()
		{
			assert(!empty());
			return _head->_next->_data;
		}
		const T& front() const
		{
			assert(!empty());
			return _head->_next->_data;
		}

		T& back()
		{
			assert(!empty());
			return _head->_prev->_data;
		}
		const T& back() const
		{
			assert(!empty());
			return _head->_prev->_data;
		}


		// Iterators
		iterator begin()
		{
			return _head->_next;
		}
		const_iterator begin() const
		{
			return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
		const_iterator end() const
		{
			return _head;
		}
		reverse_iterator rbegin()
		{
			return end();
		}
		const_reverse_iterator rbegin() const
		{
			return end();
		}
		reverse_iterator rend()
		{
			return begin();
		}
		const_reverse_iterator rend() const
		{
			return begin();
		}

		// Capacity
		bool empty() const
		{
			return _head->_next == _head;
		}
		
		size_t size() const
		{
			size_t i = 0;
			node_pointer cur = _head->_next;
			while (cur != _head)
			{
				++i;
				cur = cur->_next;
			}
			return i;
		}


		// Modifiers
		void clear()
		{
			node_pointer cur = _head->_next;
			while (cur != _head)
			{
				node_pointer tmp = cur->_next;
				delete cur;
				cur = tmp;
			}
			_head->_next = _head;
			_head->_prev = _head;
		}

		iterator insert(const_iterator pos, const T& val)
		{
			node_pointer cur = new node(val);
			node_pointer tail = pos._pnode;
			node_pointer head = tail->_prev;

			head->_next = cur;
			cur->_next = tail;

			tail->_prev = cur;
			cur->_prev = head;

			return cur;
		}
		iterator insert(const_iterator pos, size_t count, const T& val)
		{
			for (size_t i = 0; i < count; ++i)
			{
				pos = insert(pos, val);
			}
			return pos._pnode;
		}
		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			node_pointer head = pos._pnode;
			if (first != last)
			{
				head = insert(pos, *first)._pnode;
				++first;
			}
			while (first != last)
			{
				insert(pos, *first);
				++first;
			}
			return head;
		}

		iterator erase(const_iterator pos)
		{
			node_pointer tmp = pos._pnode;
			if (pos != end())
			{
				node_pointer del = tmp;
				tmp = tmp->_next;
				del->_prev->_next = del->_next;
				del->_next->_prev = del->_prev;
				delete del;
			}
			return tmp;
		}
		iterator erase(const_iterator first, const_iterator last)
		{
			while (first != last)
			{
				first = erase(first);
			}
			return last._pnode;
		}

		void push_back(const T& val)
		{
			node_pointer tmp = new node(val);
			node_pointer tail = _head->_prev;
			
			tail->_next = tmp;
			tmp->_next = _head;

			_head->_prev = tmp;
			tmp->_prev = tail;
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void swap(list<T>& val)
		{
			std::swap(_head, val._head);
		}
	
	protected:
		void empty_initialize()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}

	private:
		node_pointer _head;
	};
}