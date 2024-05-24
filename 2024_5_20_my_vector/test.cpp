#include <iostream>
#include <vector>
#include <assert.h>
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
	v1.pop_back();
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
	//it1 = v1.insert(it1 + 7, 100);
	//cout << v1 << endl;
}

int main()
{
	//test6();
	sjx::test6();
	
	return 0;
}