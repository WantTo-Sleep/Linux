#include <iostream>
using namespace std;

bool Func(int n)
{
    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() 
{
    int N = 0;
    cin >> N;
    int count = 0;
    for (int i = 2; i < N; ++i)
    {
        if (Func(i))
            ++count;
    }
    cout << count << endl;
    return 0;
}