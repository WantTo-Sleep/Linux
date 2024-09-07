// https://www.nowcoder.com/practice/56ea71d1f4e94de2aaec10e985874cce?tpId=196&tqId=40269&ru=/exam/oj

#include <unordered_set>
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums1 int整型vector 
     * @param nums2 int整型vector 
     * @return int整型vector
     */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        unordered_set<int> uset1(nums1.begin(), nums1.end());
        unordered_set<int> uset2(nums2.begin(), nums2.end());

        for (auto& e : uset2) {
            if (uset1.count(e)) {
                result.push_back(e);
            }
        }
        return result;
    }
};