// 编写一种方法，将字符串中的空格全部替换为%20。
// 假定该字符串尾部有足够的空间存放新增字符，并且知道字符串的“真实”长度。
class Solution
{
public:
    string replaceSpaces(string S, int length)
    {
        string tmp;
        int count = 0;
        for(int i = 0; i < length; ++i)
        {
            if (S[i] != ' ')
            {
                tmp += S[i];
            }
            else
            {
                tmp += "%20";
            }
        }
        return tmp;
    }
};