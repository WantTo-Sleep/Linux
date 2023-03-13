#include <iostream>
using namespace std;

#define MaxVertex 6
#define MaxDistance 9999

int main()
{
	// ͼ���ڽӾ��� ��Ȩͼ
	int graph[MaxVertex][MaxVertex] = { 0 };

	// ����ͼ
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

	// ��begin��������������·��
	int begin = 1;

	// ��ʾĳ�����㵽������������·��
	int distance[MaxVertex] = { 0 };
	// ��ʾ��û�б������Ķ���
	int visited[MaxVertex] = { 0 };
	visited[begin] = 1;

	// ����һ�� begin ָ����˭
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
		// �ҳ���û�б������Ķ����� ������̵��Ǹ�����
		for (int i = 0; i < MaxVertex; ++i)
		{
			// �����1�����������Ѿ������ʹ�����Ѱ����һ������
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
		// �����ҳ��Ķ��㵽��������ľ���
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