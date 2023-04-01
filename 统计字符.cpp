#include <iostream>
using namespace std;
// 输入一行字符，分别统计出包含英文字母、空格、数字和其它字符的个数。
int main()
{
    string str;
    getline(cin, str);
    int word = 0;
    int space = 0;
    int num = 0;
    int other = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == ' ')
            ++space;
        else if (str[i] >= '0' && str[i] <= '9')
            ++num;
        else if (str[i] >= 'a' && str[i] <= 'z')
            ++word;
        else if (str[i] >= 'A' && str[i] <= 'Z')
            ++word;
        else
            ++other;
    }

    cout << word << endl;
    cout << space << endl;
    cout << num << endl;
    cout << other << endl;

    return 0;
}