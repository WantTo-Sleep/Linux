#include <iostream>
using namespace std;

// 输出 1到n之间 的与 7 有关数字的个数。
// 一个数与7有关是指这个数是 7 的倍数
// 或者是包含 7 的数字（如 17 ，27 ，37 ... 70 ，71 ，72 ，73...）

bool HaveSeven(int i)
{
    while (i)
    {
        if (i % 10 == 7)
            return true;
        i /= 10;
    }
    return false;
}

int main()
{
    int n = 0;
    cin >> n;
    int count = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i % 7 == 0)
        {
            ++count;
        }
        else if (HaveSeven(i))
        {
            ++count;
        }
    }
    cout << count << endl;
}