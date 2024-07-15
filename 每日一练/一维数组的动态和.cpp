class Solution
{
// 给你一个数组 nums 。数组「动态和」的计算公式为：
// runningSum[i] = sum(nums[0]…nums[i]) 。
public:
    vector<int> runningSum(vector<int>& nums)
    {
        for (int i = 1; i < nums.size(); ++i)
        {
            nums[i] += nums[i - 1];
        }
        return nums;
    }
};