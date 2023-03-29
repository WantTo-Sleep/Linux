#include <iostream>
#include <vector>
using namespace std;

// 某种特殊的数列a1, a2, a3, ...的定义如下：
// a1 = 1, a2 = 2, ... , an = 2 * an − 1 + an - 2 (n > 2)。
// 给出任意一个正整数k，求该数列的第k项模以32767的结果是多少？

int main()
{
    // 数组arr存放数列
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    int n = 0;
    cin >> n;
    while (n--)
    {
        int k = 0;
        cin >> k;
        // 如果数列中不存在该数据就计算
        if (k > arr.size())
        {
            int len = arr.size();
            while (len < k)
            {
                arr.push_back((2*arr[len-1] + arr[len-2]) % 32767);
                ++len;
            }
        }
        cout << arr[k - 1] << endl;
    }
    
    return 0;
}