#include <iostream>

using namespace std;

typedef struct
{
	char name;
	int weight;
	int parent;
	int leftChild;
	int rightChild;
}HTNode;

void CreatTree(HTNode* tree, int n);
// ����
void Encode(HTNode* tree, int n);
// ����
void Decode(HTNode* tree, char* str, int n, int N);

int main()
{
	// A B C D E F G
	// 9 11 5 7 8 2 3
	// ��ʾ�м����ڵ�
	int n = 0;
	cin >> n;
	HTNode* tree = (HTNode*)malloc(sizeof(HTNode) * (2 * n - 1));
	if (tree == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	// ����ڵ����ƺ�Ȩֵ
	for (int i = 0; i < n; ++i)
	{
		cin >> tree[i].name;
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> tree[i].weight;
	}

	CreatTree(tree, n);

	Encode(tree, n);

	char str[] = "00100100111001001000100100010010";
	// char str[] = "0010010";
	// 7���ַ���ʵ���ϴ��ݵ���8�����ȣ���Ϊ����'\0'
	Decode(tree, str, n, sizeof(str) / sizeof(str[0]));

	free(tree);

	return 0;
}
void CreatTree(HTNode* tree, int n)
{
	// ��ʼ����
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		tree[i].parent = tree[i].leftChild = tree[i].rightChild = -1;
	}

	for (int j = n; j < 2 * n - 1; ++j)
	{
		// ��Ȩֵ��С���������ڵ�ϲ���һ����
		int i1 = -1, i2 = -1;
		for (int i = 0; i < j; ++i)
		{
			if (tree[i].parent == -1)
			{
				if (i1 == -1)
					i1 = i;
				if (tree[i1].weight > tree[i].weight)
				{
					i1 = i;
				}
			}
		}
		for (int i = 0; i < j; ++i)
		{
			if (tree[i].parent == -1 && i1 != i)
			{
				if (i2 == -1)
					i2 = i;
				if (tree[i2].weight > tree[i].weight)
				{
					i2 = i;
				}
			}
		}

		// ���������ϲ�
		tree[j].weight = tree[i1].weight + tree[i2].weight;
		tree[j].leftChild = i1;
		tree[j].rightChild = i2;
		tree[i1].parent = tree[i2].parent = j;
	}
	


}

void Encode(HTNode* tree, int n)
{
	// str ��������Ŷ����Ʊ���
	char* str = (char*)malloc(sizeof(char) * n);
	if (str == NULL)
	{
		exit(-1);
	}
	str[n - 1] = '\0';
	for (int i = 0; i < n; ++i)
	{
		char ch = 'A' + i;
		int start = n - 2;
		int temp = -1;
		for (int j = 0; j < n; ++j)
		{
			if (tree[j].name == ch)
			{
				temp = j;
				break;
			}
		}
		while (tree[temp].parent != -1)
		{
			if (temp == tree[tree[temp].parent].leftChild)
				str[start--] = '0';
			else
				str[start--] = '1';
			temp = tree[temp].parent;
		}
		printf("%c: %s\n", ch, &str[start + 1]);
	}
}

// N ���ַ����ĳ���
void Decode(HTNode* tree, char* str, int n, int N)
{
	int i = 0;
	while (i + 1 < N)
	{
		int parent = 2 * n - 2;
		while (i < N)
		{
			// 00 A
			if (str[i] == '0')
				parent = tree[parent].leftChild;
			else
				parent = tree[parent].rightChild;
			++i;
			if (tree[parent].leftChild == -1)
				break;

		}
		cout << tree[parent].name;
	}
}