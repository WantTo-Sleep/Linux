#include <iostream>
#include <string>
#include "BSTree.h"

using namespace std;

void TestBSTree()
{
	//BSTree<string, string> dict;
	//dict.Insert("insert", "����");
	//dict.Insert("erase", "ɾ��");
	//dict.Insert("left", "���");
	//dict.Insert("string", "�ַ���");

	//string str;
	//while (cin >> str)
	//{
	//	auto ret = dict.Find(str);
	//	if (ret)
	//	{
	//		cout << str << ":" << ret->_val << endl;
	//	}
	//	else
	//	{
	//		cout << "����ƴд����" << endl;
	//	}
	//}

	string strs[] = { "ƻ��", "����", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��" };
	// ͳ��ˮ�����ֵĴ�
	BSTree<string, int> countTree;
	for (auto str : strs)
	{
		auto ret = countTree.Find(str);
		if (ret == NULL)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_val++;
		}
	}
	countTree.InOrder();
}

int main()
{
	TestBSTree();
	return 0;
}