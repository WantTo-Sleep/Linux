class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int i = 0;

        for (auto e : nums)
        {
            i ^= e;
        }

        return i;
    }
};