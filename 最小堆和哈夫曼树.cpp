#include<iostream>
#include<deque>
using namespace std;

struct treenode
{
	int weight;
	int value;
	treenode*left;
	treenode*right;
};

typedef treenode* huffmantree;

typedef huffmantree elementtype;



struct heapstruct
{
	elementtype *arr;
	int nowsize;
	int maxsize;
};

typedef heapstruct* minheap;

//最小堆的创建
minheap create(minheap H)
{
	if (H == NULL)
	{
		H = new heapstruct;
	}
	H->arr = new elementtype[51];
	H->maxsize = 50;
	H->nowsize = 0;
	return H;
}

//最小堆的添加
minheap insert(minheap H, elementtype target)
{
	H->arr[++H->nowsize] = target;
	int child = H->nowsize;
	while(child>1)
	{
		int parent = child / 2;
		if (H->arr[parent]->weight > H->arr[child]->weight)
		{
			elementtype temp = H->arr[child];
			H->arr[child] = H->arr[parent]; 
			H->arr[parent] = temp;
			child = parent;
		}
		//父节点比子节点大
		else if (H->arr[parent]->weight <= H->arr[child]->weight)
			break;
		//父节点比子节点小，退出即可
	}
	return H;
}

//最小堆的删除
elementtype mindelete(minheap H)
{
	elementtype temp = H->arr[H->nowsize--];
	elementtype ret = H->arr[1];
	H->arr[1] = temp;
	int parent = 1;
	int child = parent * 2;
	while (child <= H->nowsize)
	{
		if (child + 1 <= H->nowsize&&H->arr[child]->weight > H->arr[child + 1]->weight)
			child++;
		if (H->arr[parent]->weight < H->arr[child]->weight)
			break;
		else if (H->arr[parent]->weight > H->arr[child]->weight)
		{
			elementtype temp = H->arr[parent];
			H->arr[parent] = H->arr[child];
			H->arr[child] = temp;
			parent = child;
			child=parent*2;
		}
	}
	return ret;
}

//最小堆的建立
minheap build(minheap H, elementtype* target, int n)
{
	for (int i = 1; i <= n; i++) {
		H->arr[i] = target[i - 1];
	}
	H->nowsize = n;

	for (int i = H->nowsize / 2; i > 0; i--)
	{
		int parent = i;
		int child = parent * 2;
		while (child<=H->nowsize)
		{
			if (child + 1 <= H->nowsize&&H->arr[child]->weight > H->arr[child + 1]->weight)
				child++;
			if (H->arr[parent]->weight < H->arr[child]->weight)
				break;
			else if (H->arr[parent]->weight > H->arr[child]->weight)
			{
				elementtype temp = H->arr[parent];
				H->arr[parent] = H->arr[child];
				H->arr[child] = temp;
				parent = child ;
				child = child * 2;
			}
		}
	}
	return H;
}

void output(minheap H)
{
	if (H == NULL)
		return;
	else
	{
		for (int i = 1; i <= H->nowsize; i++)
			cout << H->arr[i]->weight << " ";
		cout << endl;
	}
}


//哈夫曼树用指针会比较稳妥，即用指针huffmantree作为elementtype，只有这又才不会有内存的问题
huffmantree* createhuffman(huffmantree *HM, int*weights, int n)
{
	HM = new huffmantree[n];
	for (int i = 0; i < n; i++)
	{
		HM[i] = new treenode;
		HM[i]->left = NULL;
		HM[i]->right = NULL;
		HM[i]->weight = weights[i];
	}
	return HM;
}


void outputhuffman(huffmantree HM)
{
	deque<huffmantree> arr;
	arr.push_back(HM);
	while (arr.empty() == 0)
	{
		huffmantree temp = arr.front();
		arr.pop_front();
		if (temp != NULL)
		{
			cout << temp->weight << " ";
			arr.push_back(temp->left);
			arr.push_back(temp->right);
		}
	}
}



huffmantree buildhuffman(huffmantree *HM, int *weights, int n)
{
	if(HM==NULL)
		HM = createhuffman(HM, weights, n);
	minheap H = NULL;
	H = create(H);
	H = build(H, HM, n);

	while (H->nowsize != 1)
	{
		huffmantree ret = new treenode;
		ret->left = mindelete(H);
		ret->right = mindelete(H);
		ret->weight = ret->left->weight + ret->right->weight;
		H = insert(H, ret);
	}
	huffmantree hf = mindelete(H);
	return hf;
}


int main()
{
	huffmantree* hm = NULL;
	huffmantree huff = NULL;
	int weights[5] = { 3,4,1,5,2 };
	huff = buildhuffman(hm, weights, 5);
	outputhuffman(huff);
	system("pause");
}