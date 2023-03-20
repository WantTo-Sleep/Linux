#include <iostream>
using namespace std;
// 如果一个单词包含的字符个数达到或者超过10则我们认为它是一个长单词
// 所有的长单词都需要进行缩写，缩写的方法是先写下这个单词的首尾字符
// 然后再在首尾字符中间写上这个单词去掉首尾字符后所包含的字符个数
// 比如"localization"缩写后得到的是"l10n"
// "internationalization"缩写后得到的是"i18n"
// 现给出n个单词，将其中的长单词进行缩写，其余的按原样输出。
int main()
{
    int n = 0;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        int len = s.size();
        if (len < 10)
            cout << s << endl;
        else
            cout << s[0] << len - 2 << s[len - 1] << endl;
    }
}
