// 设计一个算法，算出 n 阶乘有多少个尾随零。	
class Solution
{
public:
    int trailingZeroes(int n)
    {
        int five = 0;
        while (n % 5 != 0)
            --n;
        for (int i = n; i > 4; i -= 5)
        {
            int tmp = i;
            while (tmp % 5 == 0)
            {
                ++five;
                tmp /= 5;
            }
        }
        return five;
    }
};