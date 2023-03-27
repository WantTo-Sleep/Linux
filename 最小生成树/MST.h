#include <iostream>
using namespace std;

#define MaxVertex 10
#define MaxEdge 20

typedef struct Edge
{
	int small; // 一条边的两个顶点
	int large;
	int weight;
}Edge;

typedef struct Graph
{
	int vertexNum; // 顶点数量
	int edgeNum; // 边的数量
	Edge edges[MaxEdge]; // 边的集合
}Graph;

void GraphCreat(Graph* graph);
int MinSpaTree(Graph* graph);
bool HasLoop(Graph* graph, int* child, int i);