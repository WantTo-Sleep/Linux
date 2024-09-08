// https://www.nowcoder.com/questionTerminal/2c6a0a8e1d20492f92941400036e0890

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n = 0;
    cin >> n;
	// 接下来要读入一行，getchar清楚换行符
    getchar();
    string str1, str2;
    getline(cin, str1);
	// 如果str1中没有' '，则str1或str2中至少有一个是空，直接输出-1
    size_t pos = str1.find(' ');
    if (pos == string::npos) {
        cout << -1 << endl;
    } else {
		// 得到str1和str2
        str2 = str1.substr(pos + 1);
        str1.resize(pos);
		// 采用简单贪心算法，prev1表示最近一次str1出现的位置，prev2表示最近一次str2出现的位置
        string strs;
        int prev1 = -1;
        int prev2 = -1;
        int diff = 0x7fffffff;
        for (int i = 0; i < n; ++i) {
            cin >> strs;
            if (strs == str1) {
                prev1 = i;
            }
            if (strs == str2) {
                prev2 = i;
            }
            if (prev1 != -1 && prev2 != -1) {
                diff = min(diff, abs(prev1 - prev2));
            }
        }
        if (diff == 0x7fffffff) {
            cout << -1 << endl;
        } else {
            cout << diff << endl;
        }
    }

    return 0 ;
}