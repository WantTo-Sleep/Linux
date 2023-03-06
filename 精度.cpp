#include <iostream>

using namespace std;

// 用C++语言的开方函数sqrt，连续K次开方，然后再连续K次平方，用双精度计算，结果肯定回不到原始值。
// 如果要求相差必须大于eps，请问最小的K是多少。

int main()
{
	int N = 20;
	double eps = 1.0e-10;
	// cin >> N >> eps;
	for (int i = 2; i <= N; ++i)
	{
		cout << i << "   ";
		int K = 1;
		double n0 = i;
		double n1 = i;
		while (1)
		{
			n0 = i;
			n1 = i;
			for (int j = 0; j < K; ++j)
			{
				n0 = sqrt(n0);
			}
			for (int j = 0; j < K; ++j)
			{
				n0 *= n0;
			}
			double dif = n1 - n0;
			if (dif < 0)
				dif = -dif;
			if (dif > eps)
			{
				break;
			}
			++K;
		}
		cout << K << endl;
	}
	return 0;
}