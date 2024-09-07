// https://www.nowcoder.com/practice/8d3643ec29654cf8908b5cf3a0479fd5?tpId=308&tqId=40462&ru=/exam/oj

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 优化代码
int main() {
    string str, result;
    cin >> str;

    for (auto& ch : str) {
        if ((result.size() == 0) || (result.back() != ch)) {
            result.push_back(ch);
        }
        else {
            result.pop_back();
        }
    }

    cout << (result.size() == 0 ? "0" : result) << endl;

    return 0;
}

// int main() {
//     string str;
//     cin >> str;

//     stack<char> st;
//     for (auto& ch : str) {
//         if (st.empty() || st.top() != ch) {
//             st.push(ch);
//         }
//         else if (st.top() == ch) {
//             st.pop();
//         }
//     }

//     str.clear();
//     while (!st.empty()) {
//         str.push_back(st.top());
//         st.pop();
//     }
//     reverse(str.begin(), str.end());
//     if (str.size() == 0) {
//         cout << 0 << endl;
//     }
//     else {
//         cout << str << endl;
//     }

//     return 0;
// }