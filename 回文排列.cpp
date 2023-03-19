class Solution {
public:
    bool canPermutePalindrome(string s)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            bool flag = true;
            for (int j = 1; j + i < s.size(); ++j)
            {
                if (s[j - 1] > s[j])
                {
                    swap(s[j - 1], s[j]);
                    flag = false;
                }
            }
            if (flag)
                break;
        }

        int count = 0;
        int i = s.size() - 1;
        while (!s.empty())
        {
            if (s.size() == 1)
            {
                ++count;
            }
            else if (s[i] != s[i - 1])
            {
                ++count;
                --i;
            }
            else 
            {
                s.pop_back();
                i -= 2;
            }
            s.pop_back();
        }
        return count > 1 ? false : true;
    }
};