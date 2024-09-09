// https://ac.nowcoder.com/acm/problem/221681

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    size_t n, x;
    cin >> n >> x;
    vector<ushort> a(n);
    for (auto& e : a) {
        cin >> e;
    }
    // 基础同向双指针算法
    size_t l = 0, r = 0;
    size_t minl = 0, minr = n;
    size_t sum = 0;
    while (r < n) {
        sum += a[r];
        while (sum >= x) {
            if (r - l < minr - minl) {
                minr = r;
                minl = l;
            }
            sum -= a[l];
            ++l;
        }
        ++r;
    }
    
    cout << minl + 1 << ' ' << minr + 1 << endl;
    
    return 0;
}