#include<iostream>
#include<deque>
#include<fstream>
using namespace std;

#define maxvertex 100
#define infinity 65535
typedef int Vertextype;
typedef int Weight;   //权重
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


//图邻接矩阵的建立，对拓扑排序来说，这是一个有向图
MGraph create(MGraph mg)
{
	ifstream cin("1.txt", ios::in);
	if (mg == NULL)
		mg = new Graph;
	else return mg;
	cout << "输入点的个数" << endl;
	cin >> mg->cntvertex;
	cout << "输入边的个数" << endl;
	cin >> mg->cntedge;
	for (int i = 0; i < mg->cntedge; i++)
	{
		for (int j = 0; j < mg->cntedge; j++)
			mg->edge[i][j] = infinity;
	}
	cout << "请输入各边的两个顶点以及权重" << endl;
	for (int i = 0; i < mg->cntedge; i++)
	{
		int start; int end; Weight weight;
		cin >> start >> end >> weight;
		mg->edge[start][end] = weight;
		//mg->edge[end][start] = weight;
	}
	return mg;
}

//拓扑排序
void toplogicalsort(MGraph mg, int sequence[])
{
	int cnt = 0;
	//找到入度为0的点，入队列。
	deque<int> queue;
	int indegree[100] = { 0 };      //各点的入度数目
	int visited[100] = { 0 };
	for (int i = 0; i < mg->cntvertex; i++)     //队列初始化先
	{
		int cnt = 0;
		for (int j = 0; j < mg->cntvertex; j++)
		{
			if (mg->edge[j][i] == infinity)
				cnt++;
			else
				indegree[i]++;     //各点的入度数目初始化
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
			cout << "图构成了一个环\n"; return ;
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
