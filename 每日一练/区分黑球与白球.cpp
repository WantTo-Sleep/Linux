// https://leetcode.cn/problems/separate-black-and-white-balls/?envType=daily-question&envId=2024-06-06
// 此解法数据量大时超出时间限制，正在寻找更优化的算法
class Solution
{
public:
    long long minimumSteps(string s)
    {
        long long step = 0;

        size_t last = s.size() - 1;

        while (1)
        {
            if (s[last] == '1')
            {
                if (last == 0)
                {
                    break;
                }
                s[last] = '0';
                --last;
            }
            else
            {
                size_t pos = s.find_last_of('1');
                if (pos == string::npos)
                {
                    break;
                }
                step += last - pos;
                --last;
                s[pos] = '0';
            }
        }
        return step;
    }
};