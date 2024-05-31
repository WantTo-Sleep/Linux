// https://leetcode.cn/problems/determine-if-string-halves-are-alike/
class Solution
{
public:
    bool halvesAreAlike(string s)
    {
        string::iterator _start = s.begin();
        string::iterator _end = s.end() - 1;

        string vowel("aeiouAEIOU");
        size_t num1 = 0;
        size_t num2 = 0;
        while (_start < _end)
        {
            if (vowel.find(*_start) < 10)
                ++num1;
            if (vowel.find(*_end) < 10)
                ++num2;

            ++_start;
            --_end;
        }
        return num1 == num2;
    }
};