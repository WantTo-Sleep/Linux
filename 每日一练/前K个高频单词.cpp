// https://leetcode.cn/problems/top-k-frequent-words/description/

class myCompare
{
public:
    bool operator()(pair<int, string> x, pair<int, string> y) const
    {
        if (x.first == y.first) return x.second < y.second;
        return x.first > y.first;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> countMap;
        for (auto& str : words) {
            ++countMap[str];
        }

        vector<pair<int, string>> v;
        for (auto& e : countMap) {
            v.push_back(make_pair(e.second, e.first));
        }
        sort(v.begin(), v.end(), myCompare());
        
        vector<string> result;
        for (size_t i = 0; i < k; ++i) {
            result.push_back(v[i].second);
        }
        return result;
    }
};