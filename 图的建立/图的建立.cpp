//��Ϊ�����ڽӾ��󲻺��ã�����ֻ��ʾ�ڽӱ����ʽ����ʾͼ

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
	int  point;        //�߱�����ֻ����int�ˣ���Ȼ̫�鷳�ˣ�Ҳ����˵ÿ���ߵ�����յ㶼����ű�ʾ
	Enode*next;
}EdgeNode;                   //�߱�ڵ�



typedef struct Vnode
{
	Vertextype myself;
	EdgeNode*first;
}VertexNode;                  //�����Ķ���

struct Graph
{
	int vertexnum;
	int edgenum;
	VertexNode Adjlist[maxvertexnum];
	graphtype grapht;
};

typedef Graph* MGraph;

MGraph create(MGraph mg)      //����������ͼ
{
	if (mg == NULL)
		mg = new Graph;
	else return mg;
	ifstream cin("1.txt",ios_base::in);
	if (cin.is_open() == 0)
		cout << "1:";
	//���붥����������ǵ�����
	cout << "���붥�����\n";
	cin >> mg->vertexnum;
	cout << mg->vertexnum << endl;
	cout << "���붥������\n";
	for (int i = 1; i <= mg->vertexnum; i++)
	{
		cin>>mg->Adjlist[i].myself;
		mg->Adjlist[i].first = NULL;
	}

	cout << "����ߵ���Ŀ\n";
	cin >> mg->edgenum;
	cout << "����ÿ�ԱߵĽڵ�\n";
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


//�����������   DFS
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

//�����������   BFS
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