// 题目描述：请统计某个给定范围[L, R]的所有整数中，数字2出现的次数。
//     比如给定范围[2, 22]，数字2在数2中出现了1次，在数12中出现1次，
//     在数20中出现1次，在数21中出现1次，在数22中出现2次，
//     所以数字2在该范围内一共出现了6次
// 输入描述：输入共1行，为两个正整数L和R，之间用一个空格隔开。
// 输出描述：输出共1行，表示数字2出现的次数。
// 补充说明：1 <= L <= R <= 10000。

#include <iostream>
using namespace std;
int Count2(int num)
{
	int count = 0;
	while (num)
	{
		if (num % 10 == 2) ++count;
		num /= 10;
	}
	return count;
}
int main()
{
	int left;
	int right;
	int num = 0;
	while (cin >> left >> right)
	{
		while (left <= right)
		{
			num += Count2(left);
			++left;
		}
		cout << num << endl;
	}
}