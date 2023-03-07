#include <iostream>
using namespace std;

// new 和 delet 对于内置类型

//int main()
//{
//	// new 后跟类型名可以在堆上申请该类型大小的空间
//	// 并返回该空间的首地址
//	// delet 后跟 new 的空间的首地址可以释放空间
//	int* p1 = new int;
//	cout << "p1未初始化，会是随机值" << endl << *p1 << endl << endl;
//	delete p1;
//
//	// 申请单个空间，在类型后+()可以初始化
//	double* p2 = new double(2.2);
//	cout << "p2初始化为2.2" << endl << *p2 << endl << endl;
//	delete p2;
//
//	// 申请一块连续的空间，需要在类型后+[]，里面放需要申请的个数
//	// 连续的空间在释放时 delete 后要跟[]，里面不用放数据
//	int* p3 = new int[5];
//	cout << "p3的5个元素未初始化,为随机值" << endl;
//	for (int i = 0; i < 5; ++i)
//	{
//		cout << p3[i] << " ";
//	}
//	cout << endl << endl;
//	delete[] p3;
//
//	// 申请连续的空间的初始化，需要在[]后+ {}
//	// {} 里放初始化的数据
//	int* p4 = new int[10]{ 1,2,3,4,5 };
//	cout << "p4的5个元素初始化为1，2，3，4，5，剩下5个元素应为0" << endl;
//	for (int i = 0; i < 10; ++i)
//	{
//		cout << p4[i] << " ";
//	}
//	cout << endl << endl;
//	delete[] p4;
//
//	return 0;
//}

// new 和 delete 对于自定义类型

//class Test
//{
//private:
//	int _a;
//public:
//	Test(int a = 0)
//		:_a(a)
//	{
//		cout << "Test():_a = " << _a << endl;
//	}
//	~Test()
//	{
//		cout << "~Test()" << endl;
//	}
//};
//int main()
//{
//	// 对于内置类型，new会调用其默认构造函数
//	// delete会调用其析构函数
//	Test* ptest1 = new Test;
//	delete ptest1;
//	cout << endl;
//
//	// 也可以对其进行初始化赋值
//	Test* ptest2 = new Test(20);
//	delete ptest2;
//	cout << endl;
//
//	// 开辟一块连续的自定义类型的空间
//	// new会调用n次默认构造函数，delete会调用n次析构函数
//	Test* ptest3 = new Test[5];
//	delete[] ptest3;
//	cout << endl;
//
//	// 开辟一块连续空间并初始化
//	Test* ptest4 = new Test[5]{ 1,2,3 };
//	delete[] ptest4;
//	cout << endl;
//
//	return 0;
//}

// 定位 new 表达式 : new(地址)构造函数

class Test
{
	// 为了演示方便，将成员变量设置为public
public:
	int _a;

	Test(int a = 0)
		:_a(a)
	{
		cout << "Test():_a = " << _a << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
};
int main()
{
	// 这样申请的空间并不会对这块空间初始化
	Test* ptest1 = (Test*)malloc(sizeof(Test));
	cout << ptest1->_a << endl << endl;

	// 构造函数不能显示调用，下面的语句会报错
	//ptest1->Test();
	free(ptest1);
	
	// 第一次打印应为随机值
	Test* ptest2 = (Test*)malloc(sizeof(Test));
	cout << ptest2->_a << endl;

	// 通过定位 new 表达式调用构造函数之后，打印应为 0
	new(ptest2)Test();
	cout << ptest2->_a << endl;
	ptest2->~Test();
	free(ptest2);
	cout << endl;


	// 也可以传值调用构造函数
	Test* ptest3 = (Test*)malloc(sizeof(Test));
	new(ptest3)Test(10);
	cout << ptest3->_a << endl;
	ptest3->~Test();
	free(ptest2);

	return 0;
}