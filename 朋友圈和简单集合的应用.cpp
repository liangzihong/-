#include<iostream>
using namespace std;


/*
到此为止的集合都是用数组，但是用法不一样，之前书上那个是每个元素都是一个结构体，结构体有他自己的data和他的parent
然后凭此也可以得到自己的根节点是哪一个


而这次采取了不同的措施，就是非根节点，他的值为它根节点的序号，而根节点，他的值就为他所在集合的元素个数，这个很巧妙。
而每次集合合并的操作都只为根节点操作，如果根节点不相同，说明集合不同，然后根据大小进行合并。
只用了一个数组就可以实现集合的相关。可以可以



*/



#define max 30000
typedef int elementtype;
typedef int setmark;
typedef int set[max+1];    //这个typedef就规定了set为  int set【300001】

//初始化总集合
void initset(set arr,int n)
{
	for (int i = 1; i <=n; i++) {
		arr[i] = -1;
	}
}

//将两个根节点作为参数，这样就可以只对根节点进行处理，小集合合并到大集合，则小集合根节点的值（arr[i]）变为大集合根节点，表示是大节点的子集
//然后大集合的根节点的值则变为合并后集合元素
setmark setunion(setmark root1, setmark root2, set arr)
{
	if (arr[root1] < arr[root2])   //因为集合的元素数都是相反数，所以都小于0，所以越小集合越大
	{
		arr[root1] += arr[root2];
		arr[root2] = root1;
		return root1;
	}
	else
	{
		arr[root2] += arr[root1];
		arr[root1] = root2;
		return root2;
	}
}

setmark find(elementtype x, set arr)    //寻找集合的根节点，因为在arr【i】中，arr【i】小于0的为集合根节点，大于0的不是；
										//而根节点的定义也是随便找一个就可以了。这里是默认大家初始都是-1时，则选第一个作为集合根节点
{
	if (arr[x] < 0)
		return x;
	else {
		arr[x] = find(arr[x], arr);
		return arr[x];
	}
}

//对于每一个社团，先输入第一个学生，我们把他当作是这个朋友圈集合的根节点
//假射大家都是新的，也就是第一个社团
//所以大家的值都为-1
//然后大家的根节点为1，2（输入的是1，2）
//然后两个root进行朋友圈合并
//把1作为根节点，所以arr[2]的值变为正数，意为它隶属于这个集合，而arr[1]变为-2，表示它所在集合有两个元素

//这种算法是可以的，假如本身有两个集合 1 2 3 4和5 6 7 8
//新加入的社团有1 7
//那么先对1探究，它的根节点就是1.  然后对7探究，它的根节点是5；
//然后两个朋友圈进行合并，把arr[5]的值变为1，这样即可

//我之前遇到的疑惑就是那6，7，8 好像加入不了，其实不然，因为所以操作都是针对根据根节点。
//还有疑惑就是如果一个元素属于两个社团，那要指向两个？  其实也不然，因为对每一个elementtype都是先找根节点，只对根节点操作，这个很重要
void inputconnection(set arr)
{
	int cnt;
	elementtype first;
	cin >> cnt; cin >> first;
	setmark root1, root2;       //两个根节点
	root1 = find(first, arr);   //看看first元素所在结合的根节点是哪一个，然后直接对根节点进行处理而不用在涉及其他
	for (int i = 1; i < cnt; i++)
	{
		elementtype other;
		cin >> other;
		root2 = find(other, arr);    //也是每一个元素都找到一开始它的所在集合根节点是哪一个，找到就对根节点进行处理
		if (root1 != root2)
			root1 = setunion(root1, root2, arr);
	}
}


void show(set arr,int n)
{
	int m = 1;
	elementtype value;
	for (elementtype i = 1; i <= n; i++)
	{
		if (arr[i] < 0 && -arr[i] >= m)
		{
			m = -arr[i];
			value = i;
		}
	}
	cout << "有" << m << "个" << endl;
	for (elementtype i = 1; i <= n; i++)
	{
		if (find(i, arr) == value || arr[i] == -m)      //每一个元素追根溯源看看是多少，并输出最多那个
			cout << i << " ";
	}
}


int main()
{
	set arr;
	int student, club;
	cin >> student >> club;
	initset(arr,student);
	for (int i = 0; i < club; i++)
	{
		inputconnection(arr);
	}
	show(arr, student);
	system("pause");
	return 0;
}