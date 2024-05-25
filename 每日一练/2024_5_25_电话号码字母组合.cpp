class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        // 本题采用递归的思想，先求出v需要多大的空间
        vector<string> v;
        int len = 1;
        for (int i = 0; i < digits.size(); ++i)
        {
            if (digits[i] == '7' || digits[i] == '9')
                len *= 4;
            else
                len *= 3;
        }
        // 在第三次调试中，遇到输入串为空的情况应该返回一个空的vector
        // 但是如果不加if语句，返回的就是一个含有空串的vector
        if (len == 1)
            return v;
        
        // 计算出v应该有多少个元素，resize，并递归求解
        // 这里在第一次调试时发现了错误，当时写的是
        // v.reserve(len);
        // 这导致v.begin() == v.end()，程序始终返回空。
        v.resize(len);

        insertOneNumber(v.begin(), v.end(), digits, 0);

        return v;
    }

    void insertOneNumber(vector<string>::iterator first, vector<string>::iterator last, string& digits, int i)
    {
        // 这个函数的想法是：
        // 给出需要填入空间的起始地址和结束地址
        // 再根据digits[i]确定需要填入的字母
        // 将空间分成3或4段，每一段都尾插入一个字母
        // 填完之后，划分的3或4段空间，每一段接着调用该函数填入下一个字母
        // 例如："23"，根据计算得出v的长度为3*3=9
        // 因此把这9个空间分成3份来看待，前三个空间插入'a'，中间三个空间插入'b'，最后三个空间插入'c'
        // 之后再三次调用该函数，第一次调用传入前三个空间的起始和结束地址，传入第二个字母'3'（也就是i++）
        if (i >= digits.size())
            return;
        
        char ch = digits[i];
        char ch1 = 'a';
        char ch2 = 'b';
        char ch3 = 'c';
        char ch4 = 'd';

        if (!(ch == '7' || ch == '9'))
        {
            vector<string>::iterator old_first = first;
            if (ch == '3') { ch1 = 'd'; ch2 = 'e'; ch3 = 'f'; }
            if (ch == '4') { ch1 = 'g'; ch2 = 'h'; ch3 = 'i'; }
            if (ch == '5') { ch1 = 'j'; ch2 = 'k'; ch3 = 'l'; }
            if (ch == '6') { ch1 = 'm'; ch2 = 'n'; ch3 = 'o'; }
            if (ch == '8') { ch1 = 't'; ch2 = 'u'; ch3 = 'v'; }
            // 这里第二次调试时发现了错误，当时写的是
            // gap = (last - first) / 3;
            // 没有考虑到first一直在变化
            int gap = (last - old_first) / 3;
            while (gap--)
            {
                (*first).push_back(ch1);
                ++first;
            }
            gap = (last - old_first) / 3;
            while (gap--)
            {
                (*first).push_back(ch2);
                ++first;
            }
            gap = (last - old_first) / 3;
            while (gap--)
            {
                (*first).push_back(ch3);
                ++first;
            }
            gap = (last - old_first) / 3;
            insertOneNumber(old_first, old_first + gap, digits, i + 1);
            insertOneNumber(old_first + gap, last - gap, digits, i + 1);
            insertOneNumber(last - gap, last, digits, i + 1);
        }
        else
        {
            if (ch == '7') { ch1 = 'p'; ch2 = 'q'; ch3 = 'r'; ch4 = 's'; }
            if (ch == '9') { ch1 = 'w'; ch2 = 'x'; ch3 = 'y'; ch4 = 'z'; }

            vector<string>::iterator old_first = first;
            int gap = (last - old_first) / 4;
            while (gap--)
            {
                (*first).push_back(ch1);
                ++first;
            }
            gap = (last - old_first) / 4;
            while (gap--)
            {
                (*first).push_back(ch2);
                ++first;
            }
            gap = (last - old_first) / 4;
            while (gap--)
            {
                (*first).push_back(ch3);
                ++first;
            }
            gap = (last - old_first) / 4;
            while (gap--)
            {
                (*first).push_back(ch4);
                ++first;
            }
            gap = (last - old_first) / 4;
            insertOneNumber(old_first, old_first + gap, digits, i + 1);
            insertOneNumber(old_first + gap, old_first + gap * 2, digits, i + 1);
            insertOneNumber(old_first + gap * 2, last - gap, digits, i + 1);
            insertOneNumber(last - gap, last, digits, i + 1);
        }
    }

};