// 给定两个以字符串形式表示的非负整数 num1 和 num2
// 返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
// 注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

class Solution
{
public:
    string multiply(string num1, string num2)
    {
        // 如果被乘数或者乘数为0，直接返回0
        if (num1 == "0" || num2 == "0")
            return "0";
        // 基本思想：
        // num1 * num2的每一位，再将积相加
        int len1 = num1.size();
        int len2 = num2.size();
        string result = "0";
        result.reserve(len1 + len2);

        // num2 作乘数
        for (int i = 0; i < len2; ++i)
        {
            string tmp(i, '0');
            tmp.reserve(len1 + len2);

            // 先让num2的最后一位作乘数
            int mul2 = num2[len2 - i - 1] - '0';
            // 如果乘数的某一位是0，就可以跳过本次乘法
            if (mul2 == 0)
                continue;
            int carry = 0;
            // num1 * num2的后面的一位，结果放到tmp
            for (int j = len1 - 1; j >= 0; --j)
            {
                // mul1被乘数
                int mul1 = num1[j] - '0';
                int result_tmp = mul1 * mul2 + carry;
                carry = result_tmp / 10;
                tmp += (result_tmp % 10 + '0');
            }
            if (carry > 0)
                tmp += (carry % 10 + '0');
            reverse(tmp.begin(), tmp.end());
            result = addStrings(result, tmp);
        }
        
        return result;
    }
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

        reverse(result.begin(), result.end());
        return result;
    }
};