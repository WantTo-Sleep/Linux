// 错题3
// 设已经有A，B，C，D四个类的定义，程序中A，B，C，D析构函数调用顺序
C c;
void main()
{
	A *pa = new A();
	B b;
	static D d;
	delete pa;
}
// 正解：A B D C
// 首先pa被delete，自动调用A析构函数
// 函数结束后，局部变量要被销毁，因此B析构函数被调用
// static对象与全局对象的生命周期与程序一样，程序退出时才销毁
// 同时，后定义的先销毁因此D析构函数先被调用

// 错题2
// 如果有一个类时myClass，关于下面代码正确描述：
// myClass::~myClass()
// {
//   delete this;
//   this = NULL;
// }
// 正解：它会导致栈溢出。
// 因为delete this; 会调用this指向对象的析构函数，无限递归。

// 错题1
//#include <iostream>
//using namespace std;
//int main()
//{
//	const int a = 10;
//	int* p = (int*)(&a);
//	*p = 20;
//	cout << "a = " << a << endl;
//	cout << "*p = " << *p << endl;
//
//	// 正确输出是：
//	// a = 10
//	// *p = 20
//	// 理由：const修饰的内容在C++中已经是常量了，并且在代码编译时具有宏替换的属性。
//
//	return 0;
//}