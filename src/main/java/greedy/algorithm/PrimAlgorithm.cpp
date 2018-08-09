/*
	Question Description:
		N����M���ߵ�������ͨͼ��ÿ������һ��Ȩֵ�����ͼ����С��������

		����
		��1�У�2����N,M�м��ÿո�ָ���NΪ���������MΪ�ߵ���������2 <= N <= 1000, 1 <= M <= 50000)
		��2 - M + 1�У�ÿ��3����S E W���ֱ��ʾM���ߵ�2�����㼰Ȩֵ��(1 <= S, E <= N��1 <= W <= 10000)

		���
		�����С�����������бߵ�Ȩֵ֮�͡�

		Input:
		9 14
		1 2 4
		2 3 8
		3 4 7
		4 5 9
		5 6 10
		6 7 2
		7 8 1
		8 9 7
		2 8 11
		3 9 2
		7 9 6
		3 6 4
		4 6 14
		1 8 8

		Output:
		37
	
	Analysis:
		��С��������Prim�㷨Ҳ��̰���㷨��һ�󾭵�Ӧ�á�Prim�㷨���ص���ʱ��ά��һ�������㷨���ϼӱߣ��ӵĹ���ʼ����һ������
		Prim�㷨���̣�
		һ����һ���ߵؼӣ� ά��һ������
		��ʼ E �� �����ռ��ϣ� V = ������ڵ��
		ѭ����n �C 1���Σ�ÿ��ѡ��һ���ߣ�v1,v2���� ���㣺v1����V , v2������V���ң�v1,v2��Ȩֵ��С��
		E = E + ��v1,v2��
		V = V + v2
		����E�еı���һ����С�������� V������ȫ���ڵ㡣

		Prim�㷨��֤����
		����Prim�㷨�õ�һ����P����һ����С������T������P��T��ͬ�����Ǽ���Prim�㷨���е���(K �C 1)��ʱѡ��ı߶���T�У�
		��ʱPrim�㷨������P��, ��K��ʱ,Prim�㷨ѡ����һ����e = (u, v)����T�С�����u��P���У���v���ڡ�
		��ΪT����������T�б�Ȼ��һ��u��v��·�������ǿ�������·���ϵ�һ����u��P���У����һ����v����P���У�
		��·����һ����һ����f = (x,y)��x��P���У�����y����P���С�
		���ǿ���f��e�ı�Ȩw(f)��w(e)�Ĺ�ϵ��
		��w(f) > w(e)����T����e����f ��T�м���eȥ��f)���õ�һ��Ȩֵ�͸�С������������T����С������ì�ܡ�
		��w(f) < w(e), Prim�㷨�ڵ�K��ʱӦ�ÿ��Ǽӱ�f��������e,ì�ܡ�
		���ֻ��w(f) = w(e),������T����e����f������Prim�㷨��ǰK��ѡ��ı���T���ˣ����޲�֮���T���P,����Ȩֵ�Ͳ��䣬 �Ӷ�Prim�㷨����ȷ�ġ�

		������Prim�㷨����ͼ����С������ԭ��󣬸���ôʵ������㷨��
		̰�Ĳ������ˣ�ÿһ�δ�һ�������������δ���ʹ��Ķ���ʱ��ѡ��Ȩֵ��С��·�����ʡ�
		�����������ݣ�����ͼ���ڽӾ��󣬽����ж�����һ�����С������ڽӾ���ѡ��Ȩֵ��С�Ķ������ΪP���ʣ�����P�Ӷ���ɾ����
		��P��������ѡ��ѭ����ĳ����ȫ��·��������ʵ��ظ�����Ϊֹ���Ӷ���ȡ��δ���ʵĶ������¿�ʼ��
		ֱ������Ϊ�գ��㷨������

	Created by Joseph on 2018/8/07.
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <set>
using namespace std;

struct Node
{
	bool connected;//		�Ƿ���ͨ
	bool visited;//				�Ƿ���ʹ�
	int weight;//					Ȩֵ
};

int main()
{
	int nodeCount, lineCount ;
	cin >> nodeCount;
	cin >> lineCount;

	// �������
	list<int> que(nodeCount);

	// ��¼�·��ʹ��Ľڵ�
	set<int> visitedNode;

	// ����ָ�롣������ָ�����飬�������ָ����ָ��Nodeһά����
	Node **nodeArray = new Node*[nodeCount + 1];

	for (size_t i = 1; i <= nodeCount; i++)
	{
		Node *arr = new Node[nodeCount + 1];
		for (size_t k = 1; k <= nodeCount; k++)
		{
			Node temp = {false, false, 0};
			arr[k] = temp;
		}
		nodeArray[i] = arr;

		que.push_back(i);
	}

	// �����ڽӾ���
	Node *arr, *arr2;
	Node *node, *node2;
	int p_index ;
	for (size_t i = 0; i < lineCount; i++)
	{
		int peak1, peak2, weight;
		cin >> peak1;
		cin >> peak2;
		cin >> weight;

		arr = nodeArray[peak1];
		node = &arr[peak2];
		node->connected = true;
		node->weight = weight;

		if (0 == i)
		{
			p_index = peak1;
		}

		arr2 = nodeArray[peak2];
		node2 = &arr2[peak1];
		node2->connected = true;
		node2->weight = weight;
	}

	// ѡ����ıߵ�Ȩֵ��
	int weight_sum = 0;

	/*
		�����ڽӾ������ѡ��һ��������ΪP���ʣ�����P�Ӷ���ɾ����ѡ��Ȩֵ��С�ı߷�����һ��������ΪP
		��P��������ѡ��ѭ����ĳ����ȫ��·��������ʵ��ظ�����Ϊֹ���Ӷ���ȡ��δ���ʵĶ������¿�ʼ��
		ֱ������Ϊ�գ��㷨������
	*/
	while (true)
	{
		Node *p_arr = nodeArray[p_index];

		visitedNode.insert(p_index);

		// �Ӵ����ʶ����Ƴ� p ����
		std::list<int>::iterator iter;
		for (iter = que.begin(); iter != que.end(); ++iter)
		{
			if (*iter == p_index)
			{
				iter = que.erase(iter);
			}
		}

		// �����ö��㣬�����ĸ�������ͨ����ѡ��Ȩֵ��С�ı�
		int min_node_index ;
		bool has_selected = false;
		int minWeight = 10001;// Ȩֵ��С�� 10000
		for (size_t i = 1; i <= nodeCount; i++)
		{
			if (p_arr[i].connected && 0 == visitedNode.count(i))
			{
				if (p_arr[i].weight < minWeight)
				{
					minWeight = p_arr[i].weight;
					min_node_index = i;
					has_selected = true;
				}
			}
		}

		if (has_selected)
		{
			weight_sum += minWeight;
			p_index = min_node_index;
		}
		else if (!que.empty())
		{
			p_index = que.front();
			//que.remove(p_index);
		}
		else
		{
			break;
		}
	}

	cout << weight_sum;

	/*for (size_t i = 1; i <= nodeCount; i++)
	{
		Node *arr = nodeArray[i];
		for (size_t k = 1; k <= nodeCount; k++)
		{
			Node temp = arr[k];
			cout << temp.connected << "   " << temp.visited << "    " << temp.weight << "   ";
		}
		cout << "\r\n";
	}*/

	system("pause");

	return 0;
}