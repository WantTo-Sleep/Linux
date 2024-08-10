// https://www.nowcoder.com/practice/16f59b169d904f8898d70d81d4a140a0?tpId=94&tqId=31064&rp=1&ru=%2Factivity%2Foj&qru=%2Fta%2Fbit-kaoyan%2Fquestion-ranking&tPage=2

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

bool myCompare(pair<int, string> x, pair<int, string> y) {
    if (x.first == y.first) return x.second < y.second;
    return x.first > y.first;
}

int main() {
    string str;
    getline(cin, str);

    string::iterator first = str.begin();
    string::iterator last = str.begin();
    map<string, int> countMap;
    while (last != str.end()) {
        if (*last >= 'A' && *last <= 'Z') {
            *last += 32;
        }
        if (islower(*last)) {
            ++last;
        }
        else {
            ++countMap[string(first, last)];
            ++last;
            first = last;
        }
    }

    vector<pair<int, string>> result;
    for (auto& e : countMap) {
        result.push_back(make_pair(e.second, e.first));
    }
    sort(result.begin(), result.end(), myCompare);

    for (auto& e : result) {
        cout << e.second << ':' << e.first << endl;
    }

    return 0;
}