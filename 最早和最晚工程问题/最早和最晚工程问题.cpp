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
	cout << "请输入点的个数" << endl;
	cin >> mg->cntvertex;
	cout << "请输入边的个数" << endl;
	cin >> mg->cntedge;
	cout << "请输入各点的权重" << endl;
	for (int i = 0; i < mg->cntvertex; i++)
	{
		cin >> mg->pointweight[i];
	}

	for (int i = 0; i < mg->cntvertex; i++) {            
		for (int j = 0; j < mg->cntvertex; j++) {
			mg->edge[i][j] = infinity;
		}
	}
	cout << "请输入各有向边" << endl;
	for (int i = 0; i < mg->cntedge; i++)				//顶点的权重转换为边的权重
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
	int indegree[100] = { 0 };    //入度数目为0
	int visited[100] = { 0 };
	deque<int> QUEUE;
	for (int i = 0; i < mg->cntvertex; i++)      //各点入度个数初始化
	{
		for (int j = 0; j < mg->cntvertex; j++)
		{
			if (mg->edge[j][i] != infinity)
				indegree[i]++;
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
		if (indegree[i] == 0) {
			date[i] = mg->pointweight[i];       //入度为0的话，直接date就是权重
			QUEUE.push_back(i);
		}

	while (QUEUE.size() != 0)
	{
		int k = QUEUE.front();
		QUEUE.pop_front();
		visited[k] = 1;
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (mg->edge[k][i] != infinity&&visited[i] == 0)   //i为入度为0的点的出度目标，撤销，并且date更新
			{
				indegree[i]--;
				if (date[k] + mg->edge[k][i] > date[i])    //如果有多个入度，则要选取最大的点，因为必须要全部入度都完成后才能够完成
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
			cout << "图出错了\n"; break;
		}
	}

	for (int i = 0; i < mg->cntvertex; i++)
	{
		cout << i+1 << "点完成的最早日期是：" << " " << date[i] << "天\n";
	}
}


//如果要得到最晚日期，需要将终点的日期放到latest中，然后从终点倒推，按照出度为标准，并且要多个中较小的那个

void latedate(MGraph mg, int date[],int latest)
{
	int outdegree[100] = { 0 };    //出度数目为0
	int visited[100] = { 0 };
	deque<int> QUEUE;
	for (int i = 0; i < mg->cntvertex; i++)      //各点出度个数初始化
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
			date[i] =latest;       //出度为0的话，直接date就是权重
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
			if (mg->edge[i][k] != infinity&&visited[i] == 0)   //i为出度为0的点的出度目标，撤销，并且date更新
			{
				outdegree[i]--;
				if (date[k] - mg->edge[i][k] < date[i])    //如果有多个出度，则要选取最小的点，因为必须要全部出度都完成后才能够完成
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
			cout << "图出错了\n"; break;
		}
	}
	cout << endl << endl;
	for (int i = 0; i < mg->cntvertex; i++)
	{
		cout << i+1 << "点完成的最晚日期是：" << " " << date[i] << "天\n";
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