#include<iostream>
#include<stack>
#include<vector>
using namespace std;


//这道题算法的核心是将一个数组变成两份数组。关键在于怎样判断是否出错，和是否为镜像二叉树
//柳婼的想法很6，先对数组假设进行正常二叉树后序输出，如果输出的size小于n。则假设为镜像二叉树，如果输出的size还是小于n，则不是正常二叉树

//但是实现还是我的想法（没弄懂柳婼的代码）
//因为要判断是否出错，则要看左子树的数都要比第一个小或大，右子树的数都要比第一个大或小

//如此一来，先对数组进行处理，对于正常二叉树，先找到第一个比arr[0]大的节点，这个节点right认定为右子树的root2
//所以根据数学推断，right后面的右子树是要比arr[0]大的，所以我们把right后面的比arr[0]小的都删掉（既然删掉，则size肯定比n小）
//然后根据推断，左子树的个数left=right-1（0到right之前的个数），而right=cnt-right（right到cnt的个数）。

//然后不断递归，终结条件是传来的数组只有一个数或没有数




typedef vector<int> VEC;

void foward(int*arr,int &all,int iso)   
{/*arr为完整的数组，start为第一个开始，all为全部数组的个数*/
	//首先设start=all，然后找出start作为开始。

	/*对于不是镜像二叉树，我们首先假设左子树为比arr[0]小的，那么我们则先找到第一个比arr[0]大或等于的right，如此一来，
	right后面的则全部为右子树，right前面的则为左子树。并且因为右子树都比arr[0]大，所以我们要从right到all来个搜索，
	把right后面比arr[0]小的全部去掉，然后后面的元素前移。这样一来就可以变后面操作做准备。*/

	/*而如果是镜像二叉树，则先找到第一个比arr【0】小的right，然后right后面也是右子树，前面为左子树，然后从right开始把right后面
	比arr[0]大的全部去掉，然后元素前移。*/

	if (all == 0||all==1)return;
	int start=all;
	if (iso == 0)
	{
		for (int i = 1; i < all; i++) {
			if (arr[i] >= arr[0]) { start = i; break; }
		}
		for (int i = start; i < all; i++)
		{
			if (arr[i] < arr[0])
			{
				for (int j = i; j < all-1; j++)
					arr[j] = arr[j + 1];
				all--; i--;                //因为删除一个后当前的位置为原先的下一个，所以要从当前位置重新检查
			}
		}
	}
	else
	{
		for (int i = 1; i < all; i++) {
			if (arr[i] < arr[0]) { start = i; break; }
		}
		for (int i = start; i < all; i++)
		{
			if (arr[i] >= arr[0])
			{
				for (int j = i; j < all - 1; j++)
					arr[j] = arr[j + 1];
				all--; i--;                //因为删除一个后当前的位置为原先的下一个，所以要从当前位置重新检查
			}
		}
	}
}


void select(int*arr, int cnt, int iso,VEC &ans)
{
	if (cnt == 0)return;
	foward(arr, cnt, iso);
	int left = 0;
	int right = cnt;
	//进行forward处理，再将数组分成两个数组进行左子树和右子树的递归
	if (iso == 0)
	{
		for (int i = 1; i < cnt; i++) 
		{
			if (arr[i] >= arr[0]) 
			{
				right = i; break;
			}
		}
	}
	//进行foward处理，再将数组分成两个数组进行左子树和右子树的递归
	else
	{
		for (int i = 1; i < cnt; i++) 
		{
			if (arr[i] < arr[0]) 
			{
				right = i; break;
			}
		}
	}		

	left = right - 1;
	right = cnt - right;
	select(arr + 1, left, iso, ans);    //左子树
	select(arr + left + 1, right, iso, ans);   //右子树
	ans.push_back(arr[0]);
	return;

} 

int main() 
{
	int n;
	cin >> n;
	int *arr = new int[n];
	int *arr2 = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		arr2[i] = arr[i];
	}
	VEC ans;
	int iso = 0;
	select(arr, n, iso, ans);   
	if (ans.size() == n)
	{
		cout << "YES\n";
		for (int i = 0; i < n; i++) {
			cout << ans[i];
			if (i != n - 1) cout << " ";
		}
	}
	else {
		iso = 1;
		arr = arr2;
		ans.erase(ans.begin(), ans.end());
		select(arr, n, iso, ans);
		if (ans.size() == n)
		{
			cout << "YES\n";
			for (int i = 0; i < n; i++) {
				cout << ans[i];
				if (i != n - 1) cout << " ";
			}
		}
		else cout << "NO";
	}
	system("pause");
}