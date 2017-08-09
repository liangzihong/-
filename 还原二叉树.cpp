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


//思路就是先找先序的第一个，当作是当节点。
//然后递归即可。
//但是我的代码写得比较恶心而已。。
//思路就是两个数组传进去再加个数组个数而已。。。。
bintree turntree(bintree bt, char firstarr[], char middlearr[],int n)
{
	if (n == 0)
		return 0;
	if (bt == NULL) {
		char temp = firstarr[0];  //当前char就是firstarr中的第一个
		int cnt = 0;              //找出在中序中中间那个字母的序号
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
		int i = 0;  //第二段的个数
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

//求树的高度。
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