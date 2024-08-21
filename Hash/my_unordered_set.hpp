#pragma once

#include "my_hash.hpp"

namespace sjx
{
    template <typename T>
    struct setKeyOfValue
    {
        const T &operator()(const T &x)
        {
            return x;
        }
    };

    template <typename Key, typename Hash, typename Equal>
    class unordered_set
    {
    public:
        typedef HashNode<Key> Node;
        typedef HashTable<Key, Key, setKeyOfValue<Key>, Hash, Equal> HT;
        typedef typename HT::iterator iterator;

    public:
        bool empty() const
        {
            return _table.empty();
        }
        size_t size() const
        {
            return _table.size();
        }
        std::pair<iterator, bool> insert(const Key &val)
        {
            std::pair<iterator, bool> ret = _table.Insert(val);
            return ret;
        }
        iterator find(const Key &val)
        {
            return _table.Find(val);
        }
        size_t erase(const Key &key)
        {
            return _table.Erase(key);
        }
        iterator begin()
        {
            return _table.begin();
        }
        iterator end()
        {
            return _table.end();
        }

    private:
        HT _table;
    };
}