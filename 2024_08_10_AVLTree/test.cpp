#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "AVLTree.h"

int main()
{
	srand((unsigned int)time(nullptr));

	sjx::AVLTree<int> tree;
	for (size_t i = 0; i < 100; ++i)
	{
		//tree.Inorder();
		//std::cout << std::endl;
		int ret = rand() % 100;
		//std::cout << ret << " ";
		tree.Insert(ret);
	}
	tree.Inorder();
	std::cout << std::endl;

	//sjx::AVLTree<int> tree2;
	//// std::vector<int> arr = { 76,58,32,53,44,77,70,90,67,30 };
	//std::vector<int> arr = { 42,5,38,1 };
	//for (auto& e : arr)
	//{
	//	tree2.Insert(e);
	//}

	return 0;
}