void Reverse(string& s)
{
    int start = 0, end = s.size() - 1;
    while (start < end)
    {
        swap(s[start++], s[end--]);
    }
}
class Solution
{
public:
    string reverseStr(string s, int k)
    {
        // 用来存放最终的字符串
        string tmp;

        int start = 0, end = k;
        int i = 0, len = s.size();
        while (start < len)
        {
            if (end >= len)
                end = len - 1;
            // 每次选 k 个字符生成 str
            string str(s, start, k);
            // i 用来标记次数，奇数次逆置后再连接到新的串
            if (i % 2 == 0)
                Reverse(str);
            tmp += str;
            start += k;
            end += k;
            ++i;
        }
        return tmp;
    }

};
