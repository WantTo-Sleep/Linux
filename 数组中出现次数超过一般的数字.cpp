class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int>& numbers) {
        int i = 0;
        int half = numbers.size() / 2;

        while (i < numbers.size())
        {
            int flag = 1;
            // 找与第 i 个数相同的放到 i 后面
            for (int j = i + 1; j < numbers.size(); ++j)
            {
                if (numbers[j] == numbers[i])
                {
                    swap(numbers[j], numbers[i + flag]);
                    ++flag;
                }
            }
            // 如果有一半多的数是 numbers[i] ，就结束
            if (flag <= half)
                i += flag;
            else
                break;
        }

        return numbers[i];
    }
};