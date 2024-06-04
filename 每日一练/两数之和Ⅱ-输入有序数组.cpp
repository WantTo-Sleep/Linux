// https://leetcode.cn/problems/kLl5u1/description/

// 起初只考虑到了暴力解法，但耗时太多没有通过
// 于是使用了下面的解法
class Solution
{
public:
vector<int> twoSum(vector<int>& numbers, int target)
    {
        int index1 = 0;
        int index2 = numbers.size() - 1;
        
        while (index1 < index2)
        {
            if (numbers[index1] + numbers[index2] == target)
            {
                break;
            }
            else if (numbers[index1] + numbers[index2] > target)
            {
                // 如果 min + max > target
                // 那么 任何数 + max > target
                // 即 max 不会成为加数之一
                --index2;
            }
            else
            {
                // 如果 min + max < target
                // 那么 min + 任何数 < target
                // 即 min 不会成为加数之一
                ++index1;
            }
        }

        vector<int> result;
        result.push_back(index1);
        result.push_back(index2);
        return result;
    }
	
    // vector<int> twoSum(vector<int>& numbers, int target)
    // {
    //     int index1 = 0;
    //     int index2 = 0;
        

    //     while (1)
    //     {
    //         for (index2 = index1 + 1; index2 < numbers.size(); ++index2)
    //         {
    //             if (numbers[index1] + numbers[index2] >= target)
    //             {
    //                 break;
    //             }
    //         }
    //         if (index2 == numbers.size() || numbers[index1] + numbers[index2] > target)
    //         {
    //             ++index1;
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }

    //     vector<int> result;
    //     result.push_back(index1);
    //     result.push_back(index2);
    //     return result;
    // }
};