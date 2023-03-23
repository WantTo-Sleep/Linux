// 字符串aabcccccaaa会变为a2b1c5a3
// 若“压缩”后的字符串没有变短，则返回原先的字符串
// 你可以假设字符串中只包含大小写英文字母（a至z）
class Solution
{
public:
    string compressString(string S)
    {
        if (S.size() == 0)
            return S;
        // str1用来存放压缩后的字符串
        string str1(S, 0, 1);
        // 先将S的第一个字符存入str1
        int index = 0;
        int count = 1;
        // 遍历S，如果i位置与str1的index位置所表示的字符相等，++count
        // 如果不相等，将记录的前一个字符的次数放入str1中，并加入新的字符
        for (int i = 1; i < S.size(); ++i)
        {
            if (str1[index] != S[i])
            {
                index += (1 + characterAdd(str1, count));
                str1 += S[i];
                count = 1;
            }
            else
            {
                ++count;
            }
        }
        characterAdd(str1, count);
        return S.size() <= str1.size() ? S : str1;
    }

    int characterAdd(string& str1, int count)
    {
        string str2;
        while (count)
        {
            str2 += ('0' + count % 10);
            count /= 10;
        }
        for (int i = str2.size() - 1; i >= 0; --i)
        {
            str1 += str2[i];
        }

        return str2.size();
    }
};