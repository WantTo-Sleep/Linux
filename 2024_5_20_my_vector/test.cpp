#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
using namespace std;

#include "my_vector.h"

template<class T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	/*for (size_t i = 0; i < v.size(); ++i)
	{
		out << v[i] << ' ';
	}*/

	//auto it = v.begin();
	//while (it != v.cend())
	//{
	//	out << *it << ' ';
	//	++it;
	//}

	for (auto e : v)
	{
		out << e << ' ';
	}
	return out;
}

	void test6()
	{
		vector<int> v1;
		v1.push_back(1);
		//v1.pop_back();
		v1.pop_back();

		//v1.push_back(2);
		//v1.push_back(3);
		//v1.push_back(4);
		//v1.push_back(5);
		//v1.push_back(6);
		//v1.push_back(7);

		//for (auto e : v1)
		//{
		//	cout << e << ' ';
		//}
		//cout << endl;

		//vector<int>::iterator it1 = v1.begin();
		//v1.insert(it1 + 7, 3, 10);
		//cout << v1 << endl;

		//v1.resize(0, 1);
		//cout << v1 << endl;

		//v1.resize(5, 5);
		//cout << v1 << endl;

		//v1.insert(it1, 2);
		//cout << v1 << endl;

		//vector<int>::iterator it1 = v1.begin();
		//vector<int>::iterator it2 = v1.end() - 7;
		//v1.erase(it1, it2);
		////v1.erase(v1.erase(it));
		//for (auto e : v1)
		//{
		//	cout << e << ' ';
		//}
		//cout << endl;
	}

	//void test1()
	//{
	//	vector<int> v1;
	//	v1.push_back(1);
	//	v1.push_back(2);
	//	v1.push_back(3);
	//	v1.push_back(4);
	//	v1.push_back(5);

	//	for (auto e : v1)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	for (auto& e : v1)
	//	{
	//		++e;
	//	}

	//	for (auto e : v1)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;

	//	vector<int> v2(v1.begin(), v1.end());
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}
	//	vector<int> v3(v1.begin() + 1, v1.end() - 1);
	//	for (auto e : v3)
	//	{
	//		cout << e << ' ';
	//	}
	//}
	//void test2()
	//{
	//	vector<int> v1(5, 2);
	//	vector<int> v2(10, 1);
	//	for (auto e : v1)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//}
	//void test3()
	//{
	//	vector<int> v1;
	//	v1.push_back(1);
	//	v1.push_back(2);
	//	v1.push_back(3);
	//	v1.push_back(4);
	//	v1.push_back(5);

	//	vector<int> v2(v1);
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	for (auto& e : v2)
	//	{
	//		++e;
	//	}
	//	vector<int> v3 = v2;
	//	for (auto e : v3)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//}
	//void test4()
	//{
	//	vector<int> v1;
	//	v1.push_back(1);
	//	v1.push_back(2);
	//	v1.push_back(3);
	//	v1.push_back(4);
	//	v1.push_back(5);

	//	vector<int> v2;
	//	v2 = v1;
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}

	//	vector<int> v3;
	//	v2 = v3;
	//	for (auto e : v2)
	//	{
	//		cout << e << ' ';
	//	}

	//	v1 = v1;
	//}
	//void test5()
	//{
	//	vector<int> v1;
	//	v1.resize(10, 2);
	//	cout << v1 << endl;
	//	v1.resize(3, 3);
	//	cout << v1 << endl;
	//	v1.resize(10, 3);
	//	cout << v1 << endl;

	//}

int main()
{
	//test6();
	sjx::test6();
	
	return 0;
}