#include <iostream>
using namespace std;

// 接受一个正浮点数值，输出该数值的近似整数值
// 如果小数点后数值大于等于 0.5 ,向上取整；小于 0.5 ，则向下取整。

int main()
{
    double num = 0;
    cin >> num;
    int i = (int)num;
    if (num - i >= 0.5)
        ++i;
    cout << i;
}