class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        int i = 0;
        while (i < nums.size())
        {
            int flag = 1;
            // 找与第 i 个元素相同的，找到就放到第 i 个元素后面
            for (int j = i + 1; j < nums.size() && flag < 3; ++j)
            {
                if (nums[j] == nums[i])
                {
                    swap(nums[j], nums[i + flag]);
                    ++flag;
                }
            }
            // 如果没有找到，就出现了唯一值
            if (flag == 1)
                return nums[i];
            i += 3;
        }
        return nums[nums.size() - 1];
    }
};