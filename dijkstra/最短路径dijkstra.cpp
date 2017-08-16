#include<iostream>
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


//图邻接矩阵的建立
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
		mg->edge[end][start] = weight;
	}
	return mg;
}


   
//最短路径，dijkstra算法，从v0出发到各点的最短路径,目的也是一样，把距离写在fromsp上
void dijkstra(MGraph mg, int parent[],int fromsp[])
{
	/*dijkstra算法讲究每次找到数组中的最小路径，每次找到表示v0到这个点i的最短距离为这个值*/
	/*每次找到i就更新一波，如果其他点到i距离+i到v0距离小于以前v0到i距离，就更新*/
	
	int startpoint = 0;   //从v0出发
	//int *fromsp = new int[mg->cntvertex];   //v0到每个点的最短路径，初始化为到v0的距离
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
		//从fromsp中找到当前没读过且距离最小的点
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (visited[i] != true && fromsp[i] < min)
				k = i, min = fromsp[i];
		}
		//找不到的话，图不连通
		if (k == startpoint)  //找不到小于infinity的点
		{
			cout << "图不连通\n"; break;
		}
		
		
		//找到后，通过新的节点对相应进行更新，parent，fromsp如果变小了就更新，visited更新
		visited[k] = true;
		for (int i = 0; i < mg->cntvertex; i++)
		{
			if (visited[i] != true && mg->edge[k][i] + fromsp[k] < fromsp[i])     //同过最新点与其他点连接比之前的更短
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