#include <iostream>
using namespace std;

bool Func(int i)
{
    int num = i * i;
    while (i > 0)
    {
        if (num % 10 != i % 10)
            return false;
        num /= 10;
        i /= 10;
    }
    return true;
}

int main()
{
    int n = 0;
    cin >> n;
    int count = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (Func(i))
            ++count;
    }
    cout << count << endl;
    return 0;
}