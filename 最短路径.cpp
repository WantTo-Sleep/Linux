#include <iostream>
using namespace std;

#define MaxVertex 6
#define MaxDistance 9999

int main()
{
	// 图的邻接矩阵 带权图
	int graph[MaxVertex][MaxVertex] = { 0 };

	// 创建图
	for (int i = 0; i < MaxVertex; ++i)
	{
		for (int j = 0; j < MaxVertex; ++j)
		{
			graph[i][j] = MaxDistance;
		}
	}
	graph[0][2] = 5;
	graph[0][3] = 30;
	graph[1][0] = 2;
	graph[1][4] = 8;
	graph[2][5] = 7;
	graph[2][1] = 15;
	graph[4][3] = 4;
	graph[5][3] = 10;
	graph[5][4] = 18;

	// 找begin到其他顶点的最短路径
	int begin = 1;

	// 表示某个顶点到其他顶点的最短路径
	int distance[MaxVertex] = { 0 };
	// 表示还没有遍历过的顶点
	int visited[MaxVertex] = { 0 };
	visited[begin] = 1;

	// 遍历一遍 begin 指向都有谁
	for (int i = 0; i < MaxVertex; ++i)
	{
		distance[i] = graph[begin][i];
		if (i == begin)
			distance[i] = 0;
	}

	int num = MaxVertex;
	while (--num)
	{
		int index = 0;
		// 找出在没有遍历过的顶点中 距离最短的那个顶点
		for (int i = 0; i < MaxVertex; ++i)
		{
			// 如果是1，表明顶点已经被访问过，再寻访下一个顶点
			if (visited[i] == 1)
			{
				continue;
			}
			else
			{
				if (visited[index] == 1)
				{
					index = i;
				}
				if (distance[index] > distance[i])
				{
					index = i;
				}
			}
		}
		visited[index] = 1;
		// 计算找出的顶点到其他顶点的距离
		for (int i = 0; i < MaxVertex; ++i)
		{
			if (distance[index] + graph[index][i] < distance[i])
			{
				distance[i] = distance[index] + graph[index][i];
			}
		}
	}

	for (int i = 0; i < MaxVertex; ++i)
	{
		cout << distance[i] << " ";
	}
	cout << endl;

	return 0;
}