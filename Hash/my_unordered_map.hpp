#pragma once
#include "my_hash.hpp"

namespace sjx
{
    template <typename Key, typename T>
    struct mapKeyOfValue
    {
        const Key &operator()(const std::pair<const Key, T> &x)
        {
            return x.first;
        }
    };
    template <typename T>
    struct mapEqual
    {
        bool operator()(const T &x, const T &y)
        {
            return x == y;
        }
    };
    struct stringHash
    {
        size_t operator()(const std::string &str)
        {
            size_t x = 0;
            for (size_t i = 0; i < str.size(); ++i)
            {
                x = 31 * x + str[i];
            }
            return x;
        }
    };
    template <typename Key, typename T, typename Hash = stringHash, typename Equal = mapEqual<Key>>
    class unordered_map
    {
    public:
        typedef std::pair<const Key, T> Value;
        typedef HashNode<Value> Node;
        typedef HashTable<Key, Value, mapKeyOfValue<Key, T>, Hash, Equal> HT;
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
        std::pair<iterator, bool> insert(const Value &val)
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
        T &operator[](const Key &key)
        {
            std::pair<iterator, bool> it = insert(std::make_pair(key, T()));
            return (it.first)->second;
        }

    private:
        HT _table;
    };
}