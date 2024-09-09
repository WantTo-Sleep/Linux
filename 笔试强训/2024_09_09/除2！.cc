// https://ac.nowcoder.com/acm/problem/213140

#include <iostream>
#include <queue>
using namespace std;

// 优化
int main() {
    size_t n, k;
    cin >> n >> k;
    // 定义一个堆even存放偶数，即可，遇到奇数可以直接加到结果中
    priority_queue<size_t> even;
    
    size_t a = 0;
    size_t sum = 0;
    while (n--) {
        cin >> a;
        // sum 直接 += a;
        sum += a;
        if ((a & 1) == 0) {
            even.push(a);
        }
    }
    
    while (!even.empty() && k) {
        a = even.top() / 2;
        even.pop();
        sum -= a;
        if ((a & 1) == 0) {
            even.push(a);
        }
        --k;
    }
    
    cout << sum << endl;
    
    return 0;
}

// my code
// int main() {
//     size_t n, k;
//     cin >> n >> k;
//     // 定义两个堆，odd存放奇数，even存放偶数
//     priority_queue<size_t> odd;
//     priority_queue<size_t> even;
    
//     size_t a = 0;
//     while (n--) {
//         cin >> a;
//         if ((a & 1) == 1) {
//             odd.push(a);
//         }
//         else {
//             even.push(a);
//         }
//     }
    
//     // 让偶数中的最大值 /=2
//     while (k--) {
//         if (even.empty()) {
//             break;
//         }
//         a = even.top();
//         even.pop();
//         a /= 2;
//         if ((a & 1) == 1) {
//             odd.push(a);
//         }
//         else {
//             even.push(a);
//         }
//     }
    
//     size_t sum = 0;
//     while (!odd.empty()) {
//         sum += odd.top();
//         odd.pop();
//     }
//     while (!even.empty()) {
//         sum += even.top();
//         even.pop();
//     }
    
//     cout << sum << endl;
    
//     return 0;
// }