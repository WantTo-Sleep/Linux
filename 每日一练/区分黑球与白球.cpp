// https://leetcode.cn/problems/separate-black-and-white-balls/?envType=daily-question&envId=2024-06-06

class Solution
{
public:
	// 新的解法：
	// 遍历字符串，找到'1'就计算这个与最终它应该在的位置有多远
    long long minimumSteps(string s)
    {
        long long step = 0;

		// 记录有多少个'1'
        size_t num_of_one = 0;
        for (auto e : s)
        {
            if (e == '1') ++num_of_one;
        }

        size_t tmp = num_of_one;
        size_t len = s.size();
        for (size_t i = 0; tmp; ++i)
        {
            if (s[i] == '1')
            {
				// 第一次找到'1'，它的最终位置应该在右边全'1'序列的第一个
				// 也就是len - num_of_one的位置
				// 和当前位置i相减就是它应该移动的距离
				// 之后找到'1'的最终位置在上一个'1'的后一个，所以要--tmp。
                step += len - tmp - i;
                --tmp;
            }
        }

        return step;
    }
	// 此解法数据量大时超出时间限制，正在寻找更优化的算法
    // long long minimumSteps(string s)
    // {
        // long long step = 0;

        // size_t last = s.size() - 1;

        // while (1)
        // {
            // if (s[last] == '1')
            // {
                // if (last == 0)
                // {
                    // break;
                // }
                // s[last] = '0';
                // --last;
            // }
            // else
            // {
                // size_t pos = s.find_last_of('1');
                // if (pos == string::npos)
                // {
                    // break;
                // }
                // step += last - pos;
                // --last;
                // s[pos] = '0';
            // }
        // }
        // return step;
    // }
};