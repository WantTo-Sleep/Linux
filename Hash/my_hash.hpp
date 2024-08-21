#pragma once

#include <vector>

namespace sjx
{
    template <typename T>
    struct HashNode
    {
        T _val;
        HashNode<T> *_next;

        HashNode(const T &val) : _val(val), _next(nullptr)
        {
        }
    };

    // HashTable声明，因为迭代器中需要访问HashTable中的成员
    template <typename K, typename T, typename KeyOfValue, typename Hash, typename Equal>
    class HashTable;
    template <typename K, typename T, typename KeyOfValue, typename Hash, typename Equal>
    class HashIterator
    {
        typedef HashNode<T> Node;
        typedef HashTable<K, T, KeyOfValue, Hash, Equal> HT;
        typedef HashIterator<K, T, KeyOfValue, Hash, Equal> Self;

    public:
        HashIterator(Node *node, HT *ht) : _node(node), _ht(ht)
        {
        }

        Self &operator++()
        {
            if (nullptr == _node)
                return *this;
            if (nullptr != _node->_next)
                _node = _node->_next;
            else
            {
                for (size_t hashi = _ht->Bucket(_node->_val); hashi < _ht->BucketCount(); ++hashi)
                {
                    _node = _ht->NextBucket(hashi);
                    if (nullptr != _node)
                    {
                        break;
                    }
                }
            }
            return *this;
        }
        T &operator*()
        {
            return _node->_val;
        }
        T *operator->()
        {
            return &(_node->_val);
        }
        bool operator==(Self it)
        {
            return _node == it._node;
        }
        bool operator!=(Self it)
        {
            return _node != it._node;
        }

    private:
        HT *_ht;
        Node *_node;
    };

    template <typename K, typename T, typename KeyOfValue, typename Hash, typename Equal>
    class HashTable
    {
    public:
        typedef HashNode<T> Node;
        typedef HashIterator<K, T, KeyOfValue, Hash, Equal> iterator;

    public:
        HashTable(size_t capacity = 8) : _size(0)
        {
            _table.resize(capacity, nullptr);
        }
        ~HashTable()
        {
            for (size_t i = 0; i < _table.size(); ++i)
            {
                while (_table[i] != nullptr)
                {
                    Node *del = _table[i];
                    _table[i] = del->_next;
                    delete del;
                }
            }
        }
        iterator begin()
        {
            Node *node = nullptr;
            for (size_t i = 0; i < _table.size(); ++i)
            {
                node = _table[i];
                if (node != nullptr)
                    break;
            }
            return iterator(node, this);
        }
        iterator end()
        {
            return iterator(nullptr, this);
        }
        bool empty() const
        {
            return _size == 0;
        }
        size_t size() const
        {
            return _size;
        }
        size_t Bucket(const T &val)
        {
            return _hashFunc(_kov(val)) % _table.size();
        }
        size_t BucketCount()
        {
            return _table.size();
        }
        Node *NextBucket(size_t i)
        {
            if (i + 1 >= _table.size())
                return nullptr;
            return _table[i + 1];
        }
        std::pair<iterator, bool> Insert(const T &val)
        {
            // 是否需要扩容
            if (_size * 1.0 / _table.size() > 0.8)
            {
                std::vector<Node *> newTable;
                newTable.resize(_table.size() * 2, nullptr);
                for (size_t i = 0; i < _table.size(); ++i)
                {
                    // 将旧桶中的元素放到新的桶中
                    while (_table[i] != nullptr)
                    {
                        // 找到当前元素新桶的位置
                        size_t hashi = _hashFunc(_kov(_table[i]->_val)) % newTable.size();
                        Node *old = _table[i];
                        _table[i] = old->_next;
                        old->_next = newTable[hashi];
                        newTable[hashi] = old;
                    }
                }
                _table.swap(newTable);
            }
            // 找到val应该放在哪个桶中
            size_t hashi = _hashFunc(_kov(val)) % _table.size();
            Node *bucket = _table[hashi];
            // 如果桶中有一样的key，不插入
            while (bucket != nullptr)
            {
                if (_equal(_kov(bucket->_val), _kov(val)))
                {
                    return std::make_pair(iterator(bucket, this), false);
                }
                bucket = bucket->_next;
            }
            // 没有一样的key，头插
            Node *newNode = new Node(val);
            newNode->_next = _table[hashi];
            _table[hashi] = newNode;
            ++_size;
            return std::make_pair(iterator(newNode, this), true);
        }

        iterator Find(const K &key)
        {
            size_t hashi = _hashFunc(key) % _table.size();
            Node *bucket = _table[hashi];
            while (bucket != nullptr)
            {
                if (_equal(_kov(key), _kov(bucket->_val)))
                {
                    return iterator(bucket, this);
                }
                bucket = bucket->_next;
            }
            return iterator(nullptr, this);
        }
        size_t Erase(const K &key)
        {
            size_t hashi = _hashFunc(key) % _table.size();
            Node *bucket = _table[hashi];
            Node *prev = nullptr;
            while (bucket != nullptr)
            {
                if (_equal(_kov(key), _kov(bucket->_val)))
                {
                    if (nullptr == prev)
                    {
                        _table[hashi] = bucket->_next;
                    }
                    else
                    {
                        prev->_next = bucket->_next;
                    }
                    delete bucket;
                    --_size;
                    return 1;
                }
                prev = bucket;
                bucket = bucket->_next;
            }
            return 0;
        }

    private:
        std::vector<Node *> _table;
        size_t _size;
        KeyOfValue _kov;
        Hash _hashFunc;
        Equal _equal;
    };
}