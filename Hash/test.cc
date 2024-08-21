#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <unistd.h>
#include "my_unordered_set.hpp"
#include "my_unordered_map.hpp"

struct myHash
{
    const size_t &operator()(const size_t &x)
    {
        return x;
    }
};

struct myEqual
{
    bool operator()(const size_t &x, const size_t &y)
    {
        return x == y;
    }
};

int main()
{
    srand((unsigned int)time(nullptr));
    // sjx::unordered_map<std::string, size_t> umap;
    // std::string arr[] = {"苹果", "西瓜", "香蕉", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉"};
    // for (auto &e : arr)
    // {
    //     ++umap[e];
    // }
    // for (auto &e : umap)
    // {
    //     std::cout << e.first << " : " << e.second << std::endl;
    //     sleep(1);
    // }
    sjx::unordered_set<size_t, myHash, myEqual> uset;
    std::vector<int> test = {0, 20, 22, 28, 28, 33, 42, 49, 53, 61, 61, 64, 69, 70, 70, 81, 88, 90, 95, 98};
    // sort(test.begin(), test.end());
    // for (auto& e : test)
    //     std::cout << e << ',';
    // std::cout << std::endl;

    for (auto &e : test)
        uset.insert(e);

    for (size_t i = 0; i < 50; ++i)
    {
        // sjx::unordered_set<size_t, myHash, myEqual>::iterator it = uset.find(i);
        auto it = uset.find(i);
        if (it != uset.end())
        {
            std::cout << *it << std::endl;
            int ret = uset.erase(i);
            assert(ret == 1);
        }
    }
    if (uset.erase(0) == 0)
    {
        std::cout << "没有0" << std::endl;
    }
    return 0;
}