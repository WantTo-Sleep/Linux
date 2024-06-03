// 错题1
#include <iostream>
using namespace std;
int main()
{
	const int a = 10;
	int *p = (int*)(&a);
	*p = 20;
	cout << "a = " << a << endl;
	cout << "*p = " << *p << endl;
	
	// 正确输出是：
	// a = 10
	// *p = 20
	// 理由：const修饰的内容在C++中已经是常量了，并且在代码编译时具有宏替换的属性。
	
	return 0;
}