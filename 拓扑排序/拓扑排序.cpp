#include<iostream>
#include<deque>
#include<fstream>
using namespace std;

#define maxvertex 100
#define infinity 65535
typedef int Vertextype;
typedef int Weight;   //Ȩ��
typedef Weight Distance;
typedef Distance Edge[maxvertex][maxvertex];

struct Graph
{
	int cntvertex;
	int cntedge;
	Vertextype vertex[100];
	Edge edge;
};
typedef Graph* MGraph;


//ͼ�ڽӾ���Ľ�����������������˵������һ������ͼ
MGraph create(MGraph mg)
{
	ifstream cin("1.txt", ios::in);
	if (mg == NULL)
		mg = new Graph;
	else return mg;
	cout << "�����ĸ���" << endl;
	cin >> mg->cntvertex;
	cout << "����ߵĸ���" << endl;
	cin >> mg->cntedge;
	for (int i = 0; i < mg->cntedge; i++)
	{
		for (int j = 0; j < mg->cntedge; j++)
			mg->edge[i][j] = infinity;
	}
	cout << "��������ߵ����������Լ�Ȩ��" << endl;
	for (int i = 0; i < mg->cntedge; i++)
	{
		int start; int end; Weight weight;
		cin >> start >> end >> weight;
		mg->edge[start][end] = weight;
		//mg->edge[end][start] = weight;
	}
	return mg;
}

//��������
void toplogicalsort(MGraph mg, int sequence[])
{
	int cnt = 0;
	//�ҵ����Ϊ0�ĵ㣬����С�
	deque<int> queue;
	int indegree[100] = { 0 };      //����������Ŀ
	int visited[100] = { 0 };
	for (int i = 0; i < mg->cntvertex; i++)     //���г�ʼ����
	{
		int cnt = 0;
		for (int j = 0; j < mg->cntvertex; j++)
		{
			if (mg->edge[j][i] == infinity)
				cnt++;
			else
				indegree[i]++;     //����������Ŀ��ʼ��
			if (cnt == mg->cntvertex)
				queue.push_back(i);
		}
	}


	while (queue.size() != 0)
	{
		int k = queue.front();
		sequence[cnt++] = k;
		visited[k] = 1;
		queue.pop_front();
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (mg->edge[k][i] != infinity&&visited[i]==0) {
				indegree[i]--;
				if (indegree[i] == 0)
					queue.push_back(i);
			}
		}
	}

	for (int i = 0; i < mg->cntvertex; i++) {
		if (visited[i] == 0)
		{
			cout << "ͼ������һ����\n"; return ;
		}
	}
	for (int i = 0; i < mg->cntvertex; i++) {
		cout << sequence[i]+1 << " ";
	}
	cout << endl;
	return;
}


int main()
{
	MGraph mg = NULL;
	mg = create(mg);
	int sequence[100];
	toplogicalsort(mg, sequence);
	system("pause");
	return 0;
}
