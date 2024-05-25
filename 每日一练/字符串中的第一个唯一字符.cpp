class Solution
{
public:
    int firstUniqChar(string s)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            int j = 0;
            for (; j < s.size(); ++j)
            {
                if (i == j)
                    continue;
                if (s[i] == s[j])
                    break;
            }
            if (j == s.size())
                return i;
        }
        return -1;
    }
};