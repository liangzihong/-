#include<iostream>
using namespace std;

typedef int elementtype;

struct heapstruct
{
	elementtype *arr;
	int nowsize;
	int maxsize;
};

typedef heapstruct* maxheap;


//最大堆的创建
maxheap create(maxheap H)
{
	if (H == NULL)
	{
		H = new heapstruct;
		H->maxsize = 50;
		H->nowsize = 0;
		H->arr = new elementtype[51];
	}
	return H;
}


//最大堆的建立
void build(maxheap H, elementtype *target, int n)
{
	for (int i = 0; i < n; i++)          //先将数组按层序建立一个完全二叉树（用数组表示的完全二叉树）
	{
		H->arr[i + 1] = target[i];
	}
	
	
	
	H->nowsize = n;
	int parent = H->nowsize;
	int child;
	for (int parent = n / 2; parent > 0; parent--)     //从最后一个父节点开始，每个节点都跟他们的子节点比较，拿三个中最大的上来，直到根节点
	{
		int i=parent;
		while (parent*2<=H->nowsize)         //这也是删除时从上到下过滤
		{
			child = parent * 2;
			elementtype temp = H->arr[parent];
			if (child + 1 <= H->nowsize&&H->arr[child + 1] >= H->arr[child])   //如果右子节点存在并右子节点大于左子节点
				child++;													   //目的是令child指向两个节点中最大那个
																			   //下面的动作都是与最大那个节点做的
			if (H->arr[parent] > H->arr[child])      //大于两个子节点的话，可以下一个
				break;
			else if (H->arr[parent] < H->arr[child])
			{
				H->arr[parent] = H->arr[child];
				H->arr[child] = temp;
				parent = child;
			}
		}
		parent = i;
	}
	return H;
}

//堆的输出
void output(maxheap H)
{
	for (int i = 1; i <= H->nowsize; i++) {
		cout << H->arr[i] << "  ";
	}
	cout << endl;
}

//最大堆的插入
void insert(maxheap H,elementtype target)
{
	H->arr[++H->nowsize] = target;
	int parent = H->nowsize / 2;
	int child = H->nowsize;
	elementtype temp;
	while (parent >= 1)
	{
		if (H->arr[parent] < H->arr[child])
		{
			temp = H->arr[parent];
			H->arr[parent] = H->arr[child];
			H->arr[child] = temp;
			child = parent;
			parent = parent / 2;
		}
		else
			break;
	}
	return H;
}

//最大堆的删除最大元素
elementtype heapdelete(maxheap H)
{
	elementtype temp = H->arr[H->nowsize--];
	elementtype ans = temp;
	H->arr[1] = temp;
	int parent = 1;
	int child;
	while (parent * 2 <= H->nowsize)
	{
		temp = H->arr[parent];
		child = parent * 2;
		if (child + 1 <= H->nowsize&&H->arr[child + 1] > H->arr[child])
			child++;
		if (H->arr[parent] > H->arr[child])
			break;
		else if (H->arr[parent] < H->arr[child])
		{
			H->arr[parent] = H->arr[child];
			H->arr[child] = temp;
			parent = child;
		}
	}
	return ans;
}




int main()
{
	maxheap H=create(NULL);
	elementtype arr[12] = { 79,66,43,83,30,87,38,55,91,72,49,56 };
	build(H, arr, 12);
	insert(H, 90);
	heapdelete(H);
	output(H);
	system("pause");
}