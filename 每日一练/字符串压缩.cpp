// https://leetcode.cn/problems/compress-string-lcci/description/

class Solution
{
public:
    string compressString(string S)
    {
        string result;

        string::iterator it = S.begin();
        char ch = 0;
        int num = 1;
        while (it != S.end())
        {
            if (ch == 0)
            {
                ch = *it;
            }
            else if (ch == *it)
            {
                ++num;
            }
            else
            {
                // 遇到两个不一样的字母，将之前的字母和数量写入，开始新的计数
                result += ch;
                result += digitalToString(num);
                num = 1;
                ch = *it;
            }
            ++it;
        }

        if (ch != 0)
        {
            result += ch;
            result += digitalToString(num);
        }

        return result.size() < S.size() ? result : S;
    }

    string digitalToString(int num)
    {
        std::stack<int> st;
        while (num)
        {
            st.push(num % 10);
            num /= 10;
        }
        if (st.empty())
        {
            return "0";
        }
        string result;
        while (!st.empty())
        {
            result += '0' + st.top();
            st.pop();
        }
        return result;
    }
};