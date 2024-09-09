// https://www.nowcoder.com/practice/0cfa856bf0d649b88f6260d878f35bb4?tpId=290&tqId=39937&ru=/exam/oj

#include <iostream>
#include <string>
using namespace std;

// 优秀答案
int main() {
    string s;
    // 自动跳过空格
    while (cin >> s) {
        if (s[0] <= 'z' && s[0] >= 'a') cout << (char)(s[0] - 32);
        else cout << s[0];
    }
    return 0;
}

// 我的答案
// int main() {
//     string word;
//     getline(cin, word);

//     string simple_word;
//     simple_word += toupper(word[0]);
//     for (size_t pos = 1; pos < word.size(); ++pos) {
//         if (word[pos - 1] == ' ' && isalpha(word[pos])) {
//             simple_word += toupper(word[pos]);
//         }
//     }

//     cout << simple_word << endl;

//     return 0;
// }