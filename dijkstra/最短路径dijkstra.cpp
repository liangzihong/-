#include<iostream>
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


//ͼ�ڽӾ���Ľ���
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
		mg->edge[end][start] = weight;
	}
	return mg;
}


   
//���·����dijkstra�㷨����v0��������������·��,Ŀ��Ҳ��һ�����Ѿ���д��fromsp��
void dijkstra(MGraph mg, int parent[],int fromsp[])
{
	/*dijkstra�㷨����ÿ���ҵ������е���С·����ÿ���ҵ���ʾv0�������i����̾���Ϊ���ֵ*/
	/*ÿ���ҵ�i�͸���һ������������㵽i����+i��v0����С����ǰv0��i���룬�͸���*/
	
	int startpoint = 0;   //��v0����
	//int *fromsp = new int[mg->cntvertex];   //v0��ÿ��������·������ʼ��Ϊ��v0�ľ���
	bool *visited = new bool [mg->cntvertex];
	parent[0] = -1;
	fromsp[0] = 0;
	visited[0] = true;
	for (int i = 1; i < mg->cntvertex; i++)
	{
		parent[i] = mg->edge[0][i];
		fromsp[i] = mg->edge[0][i];
		visited[i] = false;
	}

	for (int i = 1; i < mg->cntvertex; i++)
	{
		int min=infinity;
		int k=startpoint;
		//��fromsp���ҵ���ǰû�����Ҿ�����С�ĵ�
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (visited[i] != true && fromsp[i] < min)
				k = i, min = fromsp[i];
		}
		//�Ҳ����Ļ���ͼ����ͨ
		if (k == startpoint)  //�Ҳ���С��infinity�ĵ�
		{
			cout << "ͼ����ͨ\n"; break;
		}
		
		
		//�ҵ���ͨ���µĽڵ����Ӧ���и��£�parent��fromsp�����С�˾͸��£�visited����
		visited[k] = true;
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (visited[i] != true && mg->edge[k][i] + fromsp[k] < fromsp[i])     //ͬ�����µ������������ӱ�֮ǰ�ĸ���
				fromsp[i] = mg->edge[k][i] + fromsp[k], parent[i] = k;
		}
	}


}


int main()
{
	MGraph mg = NULL;
	mg = create(mg);
	int parent[100];
	int fromsp[100];
	dijkstra(mg, parent, fromsp);

	for (int i = 0; i < mg->cntvertex; i++)
	{
		cout << "0 to " << i << " : " << fromsp[i] << endl;
	}

	system("pause");
	return 0;
}