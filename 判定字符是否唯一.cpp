class Solution
{
public:
    bool isUnique(string astr)
    {
        for (int i = 0; i < astr.size(); ++i)
        {
            for (int j = i + 1; j < astr.size(); ++j)
            {
                if (astr[i] == astr[j])
                    return false;
            }
        }
        return true;
    }
};