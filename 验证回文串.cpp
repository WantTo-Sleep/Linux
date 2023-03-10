class Solution
{
public:
    bool isPalindrome(string s)
    {
        string tmp;
        for (int i = 0; i < s.size(); ++i)
        {
            char ch = s[i];
            if (ch >= 'A' && ch <= 'Z')
                tmp += ch - 'A' + 'a';
            else if (ch >= 'a' && ch <= 'z')
                tmp += ch;
            else if (ch >= '0' && ch <= '9')
                tmp += ch;
        }
		
        int start = 0, end = tmp.size() - 1;
		
        while (start < end)
        {
            if (tmp[start++] != tmp[end--])
                return false;
        }
        return true;
    }
};