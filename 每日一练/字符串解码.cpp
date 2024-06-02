// https://leetcode.cn/problems/decode-string/
class Solution
{
public:
    string decodeString(string s)
    {
        string::iterator first = s.begin();
        return func(first, s.end(), 1);
    }

    string func(string::iterator& first, string::iterator last, int i)
    {
        string result;
        string tmp;
        int count = 0;

        // 当字符串没有被遍历完，一直循环
        while (first != last)
        {
            // 如果读到的是字母，放入tmp中
            if (*first >= 'a' && *first <= 'z')
            {
                tmp += *first;
            }
            // 读到数字，记录到count中，下一次递归调用时，count表示子串重复几次
            else if (*first >= '0' && *first <= '9')
            {
                count = count * 10 + *first - '0';
            }
            // 读到'['，递归，返回的结果追加到tmp后，注意count要清零，以便下一次递归
            else if (*first == '[')
            {
                tmp += func(++first, last, count);
                count = 0;
            }
            // 读到']'，已经完整的读到了一个字串，结束循环
            else if (*first == ']')
            {
                break;
            }
            ++first;
        }
        // 重复n次字串的内容到result中
        while (i--)
        {
            result += tmp;
        }
        return result;
    }
};