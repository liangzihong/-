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
	ifstream cin("1.txt",ios::in);
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




//最小生成树，prim算法,算法目的是在parent处产生对应的路径，如parent[4]=5;则表明4，5相接。
void prim(MGraph mg, int parent[])
{
	/*n个节点的最小生成树应该有n-1条边*/
	/*parent来表示每个节点的父节点*/
	
	int startpoint = 0;							//起点从0开始
	int *fromtree = new int[mg->cntvertex];     //各点离最小生成树的最小距离。
	bool *visited=new bool [mg->cntvertex];
	visited[startpoint] = true;
	parent[startpoint] = -1;
	
	//首先以起点做为树节点，则要对parent和fromtree进行初始化
	for (int i = 1; i < mg->cntvertex; i++)
	{
		fromtree[i] = mg->edge[0][i];           //各点离树的距离
		parent[i] = 0;							//各点的父节点设为0；
		visited[i] = false;
	}

	for (int i = 1; i < mg->cntvertex; i++)            //因为要收集够mg-》cntvertex个结点
	{
		int k = findmin(mg, visited, fromtree);
		if (k)    //有小于infinity的存在，生长到新的节点，并对新的树产生相应的更新。
		{
			visited[k] = true;
			for (int i = 0; i < mg->cntvertex; i++)
			{
				if (visited[i] != true && mg->edge[k][i] < fromtree[i])   //如果其他结点离树的距离更近，则要更新离树的距离和parent
				{
					fromtree[i] = mg->edge[k][i];
					parent[i] = k;
				}
			}
		}
		else {
			cout << "图为非连通图\n";
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

	/*下面代码是测试*/
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