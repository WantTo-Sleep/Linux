#include <iostream>
#include <string>
#include "BSTree.h"

using namespace std;

void TestBSTree()
{
	//BSTree<string, string> dict;
	//dict.Insert("insert", "²åÈë");
	//dict.Insert("erase", "É¾³ý");
	//dict.Insert("left", "×ó±ß");
	//dict.Insert("string", "×Ö·û´®");

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
	//		cout << "µ¥´ÊÆ´Ð´´íÎó" << endl;
	//	}
	//}

	string strs[] = { "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Ó£ÌÒ", "Æ»¹û", "Ó£ÌÒ", "Æ»¹û", "Ó£ÌÒ", "Æ»¹û" };
	// Í³¼ÆË®¹û³öÏÖµÄ´Î
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