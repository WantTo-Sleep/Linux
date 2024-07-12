// 题目描述：牛牛拿到了一个字符串。他每次“点击”，可以把字符串中相邻两个相同字母消除，
//     例如，字符串"abbc"点击后可以生成"ac"。
//     但相同而不相邻、不相同的相邻字母都是不可以被消除的。
//     牛牛想把字符串变得尽可能短。他想知道，当他点击了足够多次之后，字符串的最终形态是什么？
// 输入描述：一个字符串，仅由小写字母组成。（字符串长度不大于300000）
// 输出描述：一个字符串，为“点击消除”后的最终形态。若最终的字符串为空串，则输出0.
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
using namespace std;
int main()
{
    string str;
    while (cin >> str)
    {
        stack<char> st;
        size_t i = str.size();
        while (i--)
        {
            if (st.empty() || st.top() != str[i])
            {
                st.push(str[i]);
            }
            else
            {
                st.pop();
            }
        }
        if (st.empty())
        {
            cout << 0 << endl;
        }
        else
        {
            while (!st.empty())
            {
                cout << st.top();
                st.pop();
            }
            cout << endl;
        }
    }
    return 0;
}