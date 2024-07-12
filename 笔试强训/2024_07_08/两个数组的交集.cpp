// 题目描述：给定两个整数数组分别为nums1，nums2，找到它们的公共元素并按返回。
// 数据范围：
// 1 <= nums1.length, nums2.length <= 1000
// 1 <= nums1[i], nums2[i] <= 1000

#include <vector>
class Solution
{
public:
    /**
    * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
    *
    *
    * @param nums1 int整型vector
    * @param nums2 int整型vector
    * @return int整型vector
    */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;
        size_t i = 0;
        size_t j = 0;
        while (i < nums1.size() && j < nums2.size())
        {
            if (nums1[i] < nums2[j])
            {
                ++i;
            }
            else if (nums1[i] > nums2[j])
            {
                ++j;
            }
            else if (!result.empty() && result.back() == nums1[i])
            {
                ++i;
                ++j;
            }
            else
            {
                result.push_back(nums1[i]);
            }
        }
        return result;
    }
}