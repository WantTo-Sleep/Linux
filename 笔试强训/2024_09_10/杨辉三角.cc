// https://www.nowcoder.com/practice/e671c6a913d448318a49be87850adbcc?tpId=290&tqId=39928&ru=/exam/oj

#include <iostream>
using namespace std;

// 用动态规划思想来解决问题
int dp[31][31];
int main() {
    int n;
    cin >> n;
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%5d", dp[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// my code
// #include <iostream>
// #include <vector>
// using namespace std;

// int main() {
//     size_t n = 0;
//     cin >> n;

//     vector<vector<size_t>> trangle;
//     for (size_t i = 0; i < n; ++i) {
//         trangle.emplace_back(i + 1, 1);

//         for (size_t j = 1; j < i; ++j) {
//             trangle[i][j] = trangle[i - 1][j - 1] + trangle[i - 1][j];
//         }
//     }

//     for (auto& e1 : trangle) {
//         for (auto e2 : e1) {
//             printf("%5lu", e2);
//         }
//         cout << endl;
//     }

//     return 0;
// }