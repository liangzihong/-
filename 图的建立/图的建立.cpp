//因为觉得邻接矩阵不好用，这里只显示邻接表的形式来表示图

#include<iostream>
#include<deque>
#include<fstream>
using namespace std;

enum graphtype{DG,UG,DN,UN};
#define maxvertexnum 100
typedef char Vertextype;

int visited[maxvertexnum] = { 0 };

typedef struct Enode
{
	int  point;        //边表的序号只能用int了，不然太麻烦了，也就是说每条边的起点终点都用序号表示
	Enode*next;
}EdgeNode;                   //边表节点



typedef struct Vnode
{
	Vertextype myself;
	EdgeNode*first;
}VertexNode;                  //顶点表的定义

struct Graph
{
	int vertexnum;
	int edgenum;
	VertexNode Adjlist[maxvertexnum];
	graphtype grapht;
};

typedef Graph* MGraph;

MGraph create(MGraph mg)      //假设是无向图
{
	if (mg == NULL)
		mg = new Graph;
	else return mg;
	ifstream cin("1.txt",ios_base::in);
	if (cin.is_open() == 0)
		cout << "1:";
	//输入顶点个数和他们的名称
	cout << "输入顶点个数\n";
	cin >> mg->vertexnum;
	cout << mg->vertexnum << endl;
	cout << "输入顶点名称\n";
	for (int i = 1; i <= mg->vertexnum; i++)
	{
		cin>>mg->Adjlist[i].myself;
		mg->Adjlist[i].first = NULL;
	}

	cout << "输入边的数目\n";
	cin >> mg->edgenum;
	cout << "输入每对边的节点\n";
	for (int i = 0; i < mg->edgenum; i++)
	{
		int start;
		int end;
		cin >> start >> end;
		EdgeNode* temp = new EdgeNode;
		temp->point = end; 
		temp->next = mg->Adjlist[start].first;
		mg->Adjlist[start].first = temp;

		EdgeNode*temp2 = new EdgeNode;
		temp2->point = start;
		temp2->next = mg->Adjlist[end].first;
		mg->Adjlist[end].first = temp2;
	}

	return mg;
}


//深度优先搜索   DFS
void DFS(MGraph mg, int point)
{
	visited[point] = 1;
	EdgeNode*temp = (mg->Adjlist)[point].first;
	for (; temp; temp = temp->next)
	{
		if (visited[temp->point] == 0) {
			cout << point << ", ";
			cout << temp->point << " ";
			cout << endl;
			DFS(mg, temp->point);
		}
	}
}

void graphdfs(MGraph mg)
{
	int startpoint = 1;
	DFS(mg, startpoint);
}

//广度优先搜索   BFS
void graphbfs(MGraph mg)
{
	deque<EdgeNode*> queue;
	int startpoint = 1;

	EdgeNode*temp = (mg->Adjlist)[startpoint].first;
	visited[startpoint] = 1;
	queue.push_back(temp);
	while (queue.size() != 0)
	{
		EdgeNode* ans = queue.front();
		queue.pop_front();
		while (ans != NULL)
		{
			startpoint = ans->point;
			if (visited[startpoint] == 0)
			{
				visited[startpoint] = 1;
				cout << startpoint << endl;
				queue.push_back((mg->Adjlist)[startpoint].first);
			}
			ans = ans->next;
		}
	}


}



int main()
{
	MGraph mg = NULL;
	mg = create(mg);
	graphbfs(mg);
	system("pause");
	return 0;
}