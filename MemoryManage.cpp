#include <iostream>
using namespace std;

// new �� delet ������������

//int main()
//{
//	// new ��������������ڶ�����������ʹ�С�Ŀռ�
//	// �����ظÿռ���׵�ַ
//	// delet ��� new �Ŀռ���׵�ַ�����ͷſռ�
//	int* p1 = new int;
//	cout << "p1δ��ʼ�����������ֵ" << endl << *p1 << endl << endl;
//	delete p1;
//
//	// ���뵥���ռ䣬�����ͺ�+()���Գ�ʼ��
//	double* p2 = new double(2.2);
//	cout << "p2��ʼ��Ϊ2.2" << endl << *p2 << endl << endl;
//	delete p2;
//
//	// ����һ�������Ŀռ䣬��Ҫ�����ͺ�+[]���������Ҫ����ĸ���
//	// �����Ŀռ����ͷ�ʱ delete ��Ҫ��[]�����治�÷�����
//	int* p3 = new int[5];
//	cout << "p3��5��Ԫ��δ��ʼ��,Ϊ���ֵ" << endl;
//	for (int i = 0; i < 5; ++i)
//	{
//		cout << p3[i] << " ";
//	}
//	cout << endl << endl;
//	delete[] p3;
//
//	// ���������Ŀռ�ĳ�ʼ������Ҫ��[]��+ {}
//	// {} ��ų�ʼ��������
//	int* p4 = new int[10]{ 1,2,3,4,5 };
//	cout << "p4��5��Ԫ�س�ʼ��Ϊ1��2��3��4��5��ʣ��5��Ԫ��ӦΪ0" << endl;
//	for (int i = 0; i < 10; ++i)
//	{
//		cout << p4[i] << " ";
//	}
//	cout << endl << endl;
//	delete[] p4;
//
//	return 0;
//}

// new �� delete �����Զ�������

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
//	// �����������ͣ�new�������Ĭ�Ϲ��캯��
//	// delete���������������
//	Test* ptest1 = new Test;
//	delete ptest1;
//	cout << endl;
//
//	// Ҳ���Զ�����г�ʼ����ֵ
//	Test* ptest2 = new Test(20);
//	delete ptest2;
//	cout << endl;
//
//	// ����һ���������Զ������͵Ŀռ�
//	// new�����n��Ĭ�Ϲ��캯����delete�����n����������
//	Test* ptest3 = new Test[5];
//	delete[] ptest3;
//	cout << endl;
//
//	// ����һ�������ռ䲢��ʼ��
//	Test* ptest4 = new Test[5]{ 1,2,3 };
//	delete[] ptest4;
//	cout << endl;
//
//	return 0;
//}

// ��λ new ���ʽ : new(��ַ)���캯��

class Test
{
	// Ϊ����ʾ���㣬����Ա��������Ϊpublic
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
	// ��������Ŀռ䲢��������ռ��ʼ��
	Test* ptest1 = (Test*)malloc(sizeof(Test));
	cout << ptest1->_a << endl << endl;

	// ���캯��������ʾ���ã���������ᱨ��
	//ptest1->Test();
	free(ptest1);
	
	// ��һ�δ�ӡӦΪ���ֵ
	Test* ptest2 = (Test*)malloc(sizeof(Test));
	cout << ptest2->_a << endl;

	// ͨ����λ new ���ʽ���ù��캯��֮�󣬴�ӡӦΪ 0
	new(ptest2)Test();
	cout << ptest2->_a << endl;
	ptest2->~Test();
	free(ptest2);
	cout << endl;


	// Ҳ���Դ�ֵ���ù��캯��
	Test* ptest3 = (Test*)malloc(sizeof(Test));
	new(ptest3)Test(10);
	cout << ptest3->_a << endl;
	ptest3->~Test();
	free(ptest2);

	return 0;
}