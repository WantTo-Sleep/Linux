#include "MST.h"

void GraphCreat(Graph* graph)
{
	cin >> graph->vertexNum >> graph->edgeNum;
	for (int i = 0; i < graph->edgeNum; ++i)
	{
		cin >> graph->edges[i].small >> graph->edges[i].large >> graph->edges[i].weight;
	}
}

int MinSpaTree(Graph* graph)
{
	int weights = 0; // 输出最短生成树的权
	int child[MaxVertex] = { 0 }; // 判断生成的树是否成环
	for (int i = 0; i < graph->vertexNum; ++i)
	{
		child[i] = i;
	}

	// 一条边一条边往树中添加
	// 树：顶点数量 = 边数量 + 1
	int edgeCount = 0;
	int i = 0; // 用来遍历每一条边
	while (edgeCount < graph->vertexNum - 1)
	{
		if (HasLoop(graph, child, i))
		{
			++i;
			continue;
		}
		cout << graph->edges[i].small << " " << graph->edges[i].large << " " << graph->edges[i].weight << endl;
		weights += graph->edges[i].weight;
		edgeCount++;
		++i;
	}
	return weights;
}

bool HasLoop(Graph* graph, int* child, int i)
{
	int ver1 = graph->edges[i].small;
	int ver2 = graph->edges[i].large;
	// 分别找两个顶点的终点
	while (ver1 != child[ver1])
	{
		ver1 = child[ver1];
	}
	while (ver2 != child[ver2])
	{
		ver2 = child[ver2];
	}

	if (ver1 == ver2)
	{
		return true;
	}
	else
	{
		if (ver1 > ver2)
		{
			child[ver2] = ver1;
		}
		else
		{
			child[ver1] = ver2;
		}
		return false;
	}
}