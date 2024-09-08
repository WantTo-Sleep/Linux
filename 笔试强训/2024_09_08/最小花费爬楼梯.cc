// https://www.nowcoder.com/practice/9b969a3ec20149e3b870b256ad40844e?tpId=230&tqId=39751&ru=/exam/oj

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 动态规划
    int n = 0;
    cin >> n;
    vector<int> costs(n);
    for (auto& e : costs) {
        cin >> e;
    }

    // 到达第i级台阶需要的总花费
    int* total_cost = new int[n + 1];
    total_cost[0] = 0; // 第0级和第一级台阶可以任选
    total_cost[1] = 0;
    for (int i = 2; i <= n; ++i) {
        // 到达第i级台阶需要的最小花费就是上一级/二级台阶的所需划分加上那一级台阶往上跳的花费
        total_cost[i] = min(total_cost[i - 1] + costs[i - 1], total_cost[i - 2] + costs[i - 2]);
    }

    cout << total_cost[n] << endl;
    
    delete[] total_cost;
    return 0;
}