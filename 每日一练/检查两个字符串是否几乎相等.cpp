// https://leetcode.cn/problems/check-whether-two-strings-are-almost-equivalent/
class Solution
{
public:
    bool checkAlmostEquivalent(string word1, string word2)
    {
        int character_count[26] = { 0 };
        
        for (auto& e : word1)
        {
            ++character_count[e - 'a'];
        }

        for (auto& e : word2)
        {
            --character_count[e - 'a'];
        }

        for (int i = 0; i < 26; ++i)
        {
            if (character_count[i] > 3 || character_count[i] < -3)
            {
                return false;
            }
        }
        return true;
    }
};