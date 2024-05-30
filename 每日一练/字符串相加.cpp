// 给定两个字符串形式的非负整数 num1 和num2
// 计算它们的和并同样以字符串形式返回。
// 你不能使用任何內建的用于处理大整数的库（比如 BigInteger）
// 也不能直接将输入的字符串转换为整数形式。

class Solution
{
public:
    string addStrings(string num1, string num2)
    {
        int len1 = num1.size() - 1;
        int len2 = num2.size() - 1;
        int carry = 0;
        string result;

        while (len1 >=0 || len2 >= 0)
        {
            int i1 = len1 >= 0 ? num1[len1--] - '0' : 0;
            int i2 = len2 >= 0 ? num2[len2--] - '0' : 0;
            int i = i1 + i2 + carry;
            if (i > 9)
            {
                i -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            result += (char)(i + '0');
        }

        if (carry == 1)
            result += '1';

        reverseString(result);
        return result;
    }
    void reverseString(string& s)
    {
        int begin = 0;
        int end = s.size() - 1;

        while (begin < end)
        {
            swap(s[begin++], s[end--]);
        }
    }
};