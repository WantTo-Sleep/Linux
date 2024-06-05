// https://leetcode.cn/problems/sort-array-by-parity-ii/description/

class Solution
{
public:
    vector<int> sortArrayByParityII(vector<int>& nums)
    {
        size_t even = 0;
        size_t odd = 1;

        while (1)
        {
            while (even < nums.size())
            {
                // 检索到在偶数下标位置的奇数
                if (nums[even] % 2 == 1)
                    break;
                even += 2;
            }
            while (odd < nums.size())
            {
                // 检索到在奇数下标位置的偶数
                if (nums[odd] % 2 == 0)
                    break;
                odd += 2;
            }
            if (even < nums.size() && odd < nums.size())
            {
                swap(nums[even], nums[odd]);
                even += 2;
                odd += 2;
            }
            else
            {
                break;
            }
        }
        return nums;
    }
};