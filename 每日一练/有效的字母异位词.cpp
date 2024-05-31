// https://leetcode.cn/problems/valid-anagram/description/
class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // 这里第一次没有考虑到，看了题解之后加上的
        if (s.length() != t.length())
        {
            return false;
        }

        // 下面是自己的思路
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        return (s.compare(t) == 0);
    }
};