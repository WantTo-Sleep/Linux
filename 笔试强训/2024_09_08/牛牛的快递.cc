// https://www.nowcoder.com/practice/41b42e7b3c3547e3acf8e90c41d98270?tpId=290&tqId=39852&ru=/exam/oj

#include <cmath>
#include <iostream>
using namespace std;

int main() {
    float a = 0;
    char b = 0;
    cin >> a >> b;

    int price = 20;
    a -= 1;
    if (a > 0)
        price += ceil(a);
    if (b == 'y')
        price += 5;

    cout << price << endl;

    return 0;
}