#include "MST.h"
//9 15
//4 7 1
//2 8 2
//0 1 3
//0 5 4
//1 8 5
//3 7 6
//1 6 6
//5 6 7
//1 2 8
//6 7 9
//3 4 10
//3 8 11
//2 3 12
//3 6 14
//4 5 18

void Test1()
{
	Graph graph;
	GraphCreat(&graph);
	cout << "最小生成树" << endl;
	int weight = MinSpaTree(&graph);
	cout << "最小权值：" << weight << endl;
}

int main()
{
	Test1();

	return 0;
}