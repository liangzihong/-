#include<iostream>
#include<algorithm>
using namespace std;

struct treenode
{
	char ch;
	treenode*left;
	treenode*right;
};

typedef treenode* bintree;


//˼·������������ĵ�һ���������ǵ��ڵ㡣
//Ȼ��ݹ鼴�ɡ�
//�����ҵĴ���д�ñȽ϶��Ķ��ѡ���
//˼·�����������鴫��ȥ�ټӸ�����������ѡ�������
bintree turntree(bintree bt, char firstarr[], char middlearr[],int n)
{
	if (n == 0)
		return 0;
	if (bt == NULL) {
		char temp = firstarr[0];  //��ǰchar����firstarr�еĵ�һ��
		int cnt = 0;              //�ҳ����������м��Ǹ���ĸ�����
		bt = new treenode;		
		bt->left = NULL;
		bt->right = NULL;
		bt->ch = temp;
		if (n == 1)
			return bt;
		char *firstinstead = new char[n + 1];
		char *secondstead = new char[n + 1];
		for (; cnt < n; cnt++)
		{
			if (middlearr[cnt] != temp)
			{
				firstinstead[cnt] = firstarr[cnt + 1];
				secondstead[cnt] = middlearr[cnt];
			}
			else break;
		}
		bt->left = turntree(bt->left, firstinstead, secondstead, cnt);
		int i = 0;  //�ڶ��εĸ���
		cnt++;
		for (; cnt < n; cnt++, i++)
		{
			firstinstead[i] = firstarr[cnt];
			secondstead[i] = middlearr[cnt];
		}
		bt->right = turntree(bt->right, firstinstead, secondstead, i);
		delete[]firstinstead;
		delete[]secondstead;
	}
	return bt;
}

//�����ĸ߶ȡ�
int getheight(bintree bt)
{
	int height = 0;
	if (bt == NULL)
		return 0;
	int left = getheight(bt->left);
	int right = getheight(bt->right);
	height = ((left > right) ? left : right)+1;
	return height;
}


int main()
{
	int cnt;
	cin >> cnt;
	char *first = new char[cnt+1];
	char *second = new char[cnt+1];
	cin >> first;
	cin >> second;
	bintree bt = NULL;
	bt = turntree(bt, first, second, cnt);
	cout << getheight(bt) << endl;
	system("pause");
	return 0;
}