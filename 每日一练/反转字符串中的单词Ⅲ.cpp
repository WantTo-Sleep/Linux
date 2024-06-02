// 给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序
// 同时仍保留空格和单词的初始顺序。
class Solution
{
public:
    string reverseWords(string s)
    {
        int pos = 0;
        for (int i = 0; i < s.size(); i = pos)
        {
            pos = s.find(' ', pos);
            if (pos < i)
            {
                reverseString(s, i, s.size() - 1);
                return s;
            }
            reverseString(s, i, pos - 1);
            ++pos;
        }
        return s;
    }
    void reverseString(string& s, int begin, int end)
    {
        while (begin < end)
        {
            swap(s[begin++], s[end--]);
        }
    }
};