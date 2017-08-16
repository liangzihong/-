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
	ifstream cin("1.txt",ios::in);
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
		cin >> start >> end>>weight;
		mg->edge[start][end] = weight;
		mg->edge[end][start] = weight;
	}
	return mg;
}


int findmin(MGraph mg, bool visited[],int fromtree[])
{
	int min = infinity;
	int cnt = 0;
	for (int i = 0; i < mg->cntvertex;i++)
	{
		if (visited[i] == false && fromtree[i] < min)
		{
			min = fromtree[i];
			cnt = i;
		}
	}
	return cnt;
}




//��С��������prim�㷨,�㷨Ŀ������parent��������Ӧ��·������parent[4]=5;�����4��5��ӡ�
void prim(MGraph mg, int parent[])
{
	/*n���ڵ����С������Ӧ����n-1����*/
	/*parent����ʾÿ���ڵ�ĸ��ڵ�*/
	
	int startpoint = 0;							//����0��ʼ
	int *fromtree = new int[mg->cntvertex];     //��������С����������С���롣
	bool *visited=new bool [mg->cntvertex];
	visited[startpoint] = true;
	parent[startpoint] = -1;
	
	//�����������Ϊ���ڵ㣬��Ҫ��parent��fromtree���г�ʼ��
	for (int i = 1; i < mg->cntvertex; i++)
	{
		fromtree[i] = mg->edge[0][i];           //���������ľ���
		parent[i] = 0;							//����ĸ��ڵ���Ϊ0��
		visited[i] = false;
	}

	for (int i = 1; i < mg->cntvertex; i++)            //��ΪҪ�ռ���mg-��cntvertex�����
	{
		int k = findmin(mg, visited, fromtree);
		if (k)    //��С��infinity�Ĵ��ڣ��������µĽڵ㣬�����µ���������Ӧ�ĸ��¡�
		{
			visited[k] = true;
			for (int i = 0; i < mg->cntvertex; i++)
			{
				if (visited[i] != true && mg->edge[k][i] < fromtree[i])   //���������������ľ����������Ҫ���������ľ����parent
				{
					fromtree[i] = mg->edge[k][i];
					parent[i] = k;
				}
			}
		}
		else {
			cout << "ͼΪ����ͨͼ\n";
			break;
		}
	}

}



int main()
{
	MGraph mg = NULL;
	mg = create(mg);
	int parent[100];
	prim(mg, parent);

	/*��������ǲ���*/
	int sum = 0;
	for (int i = 0; i < mg->cntvertex; i++)
	{
		if (~parent[i])
			sum += mg->edge[i][parent[i]];
	}
	cout << sum << endl;
	system("pause");
	return 0;
}