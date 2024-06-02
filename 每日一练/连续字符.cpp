// https://leetcode.cn/problems/consecutive-characters/

class Solution
{
public:
    int maxPower(string s)
    {
        int power = 1;
        int tmp = 1;
        for (int i = 1; i < s.size(); ++i)
        {
            if (s[i] == s[i - 1])
            {
                ++tmp;
            }
            else
            {
                power = tmp > power ? tmp : power;
                tmp = 1;
            }
        }
        power = tmp > power ? tmp : power;
        return power;
    }
};