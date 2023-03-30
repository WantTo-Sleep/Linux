// 将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数
// 数值为 0 或者字符串不是一个合法的数值则返回 0

class Solution
{
public:
    int StrToInt(string str)
    {
        int num = 0;
        int flag = 1;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                num = num * 10 + str[i] - '0';
            }
            else if (str[i] == '-' && i == 0)
            {
                flag = -1;
            }
            else if (str[i] == '+' && i == 0)
            {
                continue;
            }
            else
            {
                num = 0;
                break;
            }
        }
        return num * flag;
    }
};