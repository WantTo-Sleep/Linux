class Solution
{
public:
    bool CheckPermutation(string s1, string s2)
	{
        if (s1.size() != s2.size())
            return false;
		
        for (int i = 0; i < s1.size(); ++i)
        {
            int flag = 1;
            for (int j = 1; j + i < s1.size(); ++j)
            {
                if (s1[j - 1] > s1[j])
                {
                    swap(s1[j - 1], s1[j]);
                    flag = 0;
                }
                if (s2[j - 1] > s2[j])
                {
                    swap(s2[j - 1], s2[j]);
                    flag = 0;
                }
            }
            if (flag)
                break;
        }
		
        for (int i = 0; i < s1.size(); ++i)
        {
            if (s1[i] != s2[i])
                return false;
        }
        return true;
    }
};