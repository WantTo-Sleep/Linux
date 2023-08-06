class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int pos = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (nums[pos] != nums[i])
            {
                swap(nums[++pos], nums[i]);
            }
        }
        return pos + 1;
    }
};