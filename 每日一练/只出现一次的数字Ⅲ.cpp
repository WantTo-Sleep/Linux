class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums)
    {
        vector<int> result;
        result.reserve(2);

        size_t i = 0;
        while (i < nums.size() && result.size() < 2)
        {
            int flag = 1;
            // 先找与第一个数相同的数放到其后面
            for (int j = i + 1; j < nums.size(); ++j)
            {
                if (nums[i] == nums[j])
                {
                    swap(nums[i + 1], nums[j]);
                    ++flag;
                    break;
                }
            }
            // 没找到就表明这个数只出现一次，放到结果中
            if (flag == 1)
            {
                result.push_back(nums[i]);
            }
            // 继续找下一个
            i += flag;
        }

        return result;
    }
};