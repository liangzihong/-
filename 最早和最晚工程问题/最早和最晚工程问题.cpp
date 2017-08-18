#include<iostream>
#include<vector>
#include<deque>
#include<fstream>
using namespace std;
#define infinity 65535

typedef int Vertextype;
typedef int Weight;
typedef Weight Edge[100][100];

struct Graph
{
	int cntvertex;
	int cntedge;
	Weight pointweight[100];
	Edge edge;
};

typedef Graph* MGraph;

MGraph create(MGraph mg)
{
	if (mg != NULL)
		return mg;
	mg = new Graph;
	ifstream cin("1.txt", ios::in);
	cout << "�������ĸ���" << endl;
	cin >> mg->cntvertex;
	cout << "������ߵĸ���" << endl;
	cin >> mg->cntedge;
	cout << "����������Ȩ��" << endl;
	for (int i = 0; i < mg->cntvertex; i++)
	{
		cin >> mg->pointweight[i];
	}

	for (int i = 0; i < mg->cntvertex; i++) {            
		for (int j = 0; j < mg->cntvertex; j++) {
			mg->edge[i][j] = infinity;
		}
	}
	cout << "������������" << endl;
	for (int i = 0; i < mg->cntedge; i++)				//�����Ȩ��ת��Ϊ�ߵ�Ȩ��
	{
		int a, b;
		cin >> a >> b;
		a--; b--;     
		mg->edge[a][b] = mg->pointweight[b];
	}
	return mg;
}



void earlydate(MGraph mg, int date[])
{
	int indegree[100] = { 0 };    //�����ĿΪ0
	int visited[100] = { 0 };
	deque<int> QUEUE;
	for (int i = 0; i < mg->cntvertex; i++)      //������ȸ�����ʼ��
	{
		for (int j = 0; j < mg->cntvertex; j++)
		{
			if (mg->edge[j][i] != infinity)
				indegree[i]++;
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
		if (indegree[i] == 0) {
			date[i] = mg->pointweight[i];       //���Ϊ0�Ļ���ֱ��date����Ȩ��
			QUEUE.push_back(i);
		}

	while (QUEUE.size() != 0)
	{
		int k = QUEUE.front();
		QUEUE.pop_front();
		visited[k] = 1;
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (mg->edge[k][i] != infinity&&visited[i] == 0)   //iΪ���Ϊ0�ĵ�ĳ���Ŀ�꣬����������date����
			{
				indegree[i]--;
				if (date[k] + mg->edge[k][i] > date[i])    //����ж����ȣ���Ҫѡȡ���ĵ㣬��Ϊ����Ҫȫ����ȶ���ɺ���ܹ����
					date[i] = date[k] + mg->edge[k][i];
				if (indegree[i] == 0)
					QUEUE.push_back(i);
			}
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
	{
		if(date[i]==0)
		{
			cout << "ͼ������\n"; break;
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
	{
		cout << i+1 << "����ɵ����������ǣ�" << " " << date[i] << "��\n";
	}
}


//���Ҫ�õ��������ڣ���Ҫ���յ�����ڷŵ�latest�У�Ȼ����յ㵹�ƣ����ճ���Ϊ��׼������Ҫ����н�С���Ǹ�

void latedate(MGraph mg, int date[],int latest)
{
	int outdegree[100] = { 0 };    //������ĿΪ0
	int visited[100] = { 0 };
	deque<int> QUEUE;
	for (int i = 0; i < mg->cntvertex; i++)      //������ȸ�����ʼ��
	{
		for (int j = 0; j < mg->cntvertex; j++)
		{
			if (mg->edge[i][j] != infinity)
				outdegree[i]++;
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
	{
		if (outdegree[i] == 0) {
			date[i] =latest;       //����Ϊ0�Ļ���ֱ��date����Ȩ��
			QUEUE.push_back(i);
		}
		else
			date[i] = 9999;
	}
		

	while (QUEUE.size() != 0)
	{
		int k = QUEUE.front();
		QUEUE.pop_front();
		visited[k] = 1;
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (mg->edge[i][k] != infinity&&visited[i] == 0)   //iΪ����Ϊ0�ĵ�ĳ���Ŀ�꣬����������date����
			{
				outdegree[i]--;
				if (date[k] - mg->edge[i][k] < date[i])    //����ж�����ȣ���Ҫѡȡ��С�ĵ㣬��Ϊ����Ҫȫ�����ȶ���ɺ���ܹ����
					date[i] = date[k] - mg->edge[i][k];
				if (outdegree[i] == 0)
					QUEUE.push_back(i);
			}
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
	{
		if (date[i] == 0)
		{
			cout << "ͼ������\n"; break;
		}
	}
	cout << endl << endl;
	for (int i = 0; i < mg->cntvertex; i++)
	{
		cout << i+1 << "����ɵ����������ǣ�" << " " << date[i] << "��\n";
	}
}

int main()
{
	MGraph mg = NULL;
	mg = create(mg);
	int eardate[100] = { 0 };
	int ladate[100];
	earlydate(mg, eardate);
	latedate(mg, ladate,eardate[mg->cntvertex-1]);
	system("pause");
	return 0;
}