#include <iostream>
#include <queue>
using namespace std;
#define MaxVertexNum 10

typedef char VertexType;
typedef struct Graph
{
	int verNum;
	int edgeNum;
	int arr[MaxVertexNum][MaxVertexNum];
}Graph;

void GraphAddEdge(Graph* graph, VertexType ver1, VertexType ver2, VertexType* verName);

// BFS_广度优先遍历
void BFS(Graph& graph, VertexType ver, int* visited, queue<VertexType>& q)
{
	q.push(ver);
	while (!q.empty())
	{
		VertexType temp = q.front();
		q.pop();
		temp = temp - 'A';
		if (visited[temp])
			continue;
		visited[temp] = 1;
		printf("%d ", temp);
		for (int i = 0; i < graph.verNum; ++i)
		{
			if (graph.arr[temp][i])
			{
				q.push(i + 'A');
			}
		}
	}
}

int main()
{
	// 顶点的数量
	Graph graph;
	for (int i = 0; i < MaxVertexNum; ++i)
	{
		for (int j = 0; j < MaxVertexNum; ++j)
		{
			graph.arr[i][j] = 0;
		}
	}
	cin >> graph.verNum >> graph.edgeNum;

	// 读入顶点的名字,相当于给顶点编号
	VertexType* verName = (VertexType*)malloc(sizeof(VertexType) * graph.verNum);
	if (verName == NULL)
	{
		perror("verName");
	}
	for (int i = 0; i < graph.verNum; ++i)
	{
		cin >> verName[i];
	}

	// 读顶点的边
	int edgeNum = graph.edgeNum;
	while (edgeNum--)
	{
		VertexType ver1, ver2;
		cin >> ver1 >> ver2;
		GraphAddEdge(&graph, ver1, ver2, verName);
	}

	int visited[MaxVertexNum] = { 0 };
	queue<VertexType> q;

	BFS(graph, 'C', visited, q);

	free(verName);

	return 0;
}


void GraphAddEdge(Graph* graph, VertexType ver1, VertexType ver2, VertexType* verName)
{
	int i = 0, j = 0;
	while (ver1 != verName[i])
	{
		++i;
	}
	while (ver2 != verName[j])
	{
		++j;
	}
	graph->arr[i][j] = graph->arr[j][i] = 1;
}

//// DFS_深度优先遍历
//void DFS(Graph* graph, VertexType V, int* visited)
//{
//	if (visited[V - 'A'])
//	{
//		return;
//	}
//	printf("%d ", V - 'A');
//	visited[V - 'A'] = 1;
//	for (int i = 0; i < graph->verNum; ++i)
//	{
//		if (graph->arr[V - 'A'][i])
//		{
//			DFS(graph, 'A' + i, visited);
//		}
//	}
//}
//
//int main()
//{
//	// 顶点的数量
//	Graph graph;
//	for (int i = 0; i < MaxVertexNum; ++i)
//	{
//		for (int j = 0; j < MaxVertexNum; ++j)
//		{
//			graph.arr[i][j] = 0;
//		}
//	}
//	cin >> graph.verNum >> graph.edgeNum;
//
//	// 读入顶点的名字,相当于给顶点编号
//	VertexType* verName = (VertexType*)malloc(sizeof(VertexType) * graph.verNum);
//	if (verName == NULL)
//	{
//		perror("verName");
//	}
//	for (int i = 0; i < graph.verNum; ++i)
//	{
//		cin>>verName[i];
//	}
//
//	// 读顶点的边
//	int edgeNum = graph.edgeNum;
//	while (edgeNum--)
//	{
//		VertexType ver1, ver2;
//		cin >> ver1 >> ver2;
//		GraphAddEdge(&graph, ver1, ver2, verName);
//	}
//
//	//for (int i = 0; i < MaxVertexNum; ++i)
//	//{
//	//	for (int j = 0; j < MaxVertexNum; ++j)
//	//	{
//	//		printf("%d ", graph.arr[i][j]);
//	//	}
//	//	printf("\n");
//	//}
//
//	//// 输出每个顶点的度
//	//for (int i = 0; i < graph.verNum; ++i)
//	//{
//	//	printf("%c:", verName[i]);
//	//	int sum = 0;
//	//	for (int j = 0; j < graph.verNum; ++j)
//	//	{
//	//		sum += graph.arr[i][j];
//	//	}
//	//	printf("%d\n", sum);
//	//}
//
//	int visited[MaxVertexNum] = { 0 };
//	DFS(&graph, 'F', visited);
//
//	free(verName);
//
//	return 0;
//}
