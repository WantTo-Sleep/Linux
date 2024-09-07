// https://www.nowcoder.com/practice/179d9754eeaf48a1b9a49dc1d438525a?tpId=290&tqId=39941&ru=/exam/oj

#include <iostream>
using namespace std;

int main() {
    int left = 0;
    int right = 0;
    cin >> left >> right;

    int count = 0;
    while (left <= right) {
        int temp = left;
        while (temp != 0) {
            if (temp % 10 == 2)
                ++count;
            temp /= 10;
        }
        ++left;
    }

    cout << count << endl;

    return 0;
}