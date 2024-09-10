// https://www.nowcoder.com/practice/18ecd0ecf5ef4fe9ba3f17f8d00d2d66?tpId=122&tqId=33668&ru=/exam/oj

#include <iostream>
using namespace std;

int main() {
    size_t N = 0;
    cin >> N;

    size_t a = 0, b = 1;
    // 找到离N最近的两个斐波那契数
    while (N > b) {
        size_t c = a + b;
        a = b;
        b = c;
    }
    // 两者取其近
    size_t diff = N - a;
    diff = diff > b - N ? b - N : diff;
    cout << diff << endl;

    return 0;
}