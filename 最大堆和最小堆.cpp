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


//���ѵĴ���
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


//���ѵĽ���
void build(maxheap H, elementtype *target, int n)
{
	for (int i = 0; i < n; i++)          //�Ƚ����鰴������һ����ȫ���������������ʾ����ȫ��������
	{
		H->arr[i + 1] = target[i];
	}
	
	
	
	H->nowsize = n;
	int parent = H->nowsize;
	int child;
	for (int parent = n / 2; parent > 0; parent--)     //�����һ�����ڵ㿪ʼ��ÿ���ڵ㶼�����ǵ��ӽڵ�Ƚϣ�������������������ֱ�����ڵ�
	{
		int i=parent;
		while (parent*2<=H->nowsize)         //��Ҳ��ɾ��ʱ���ϵ��¹���
		{
			child = parent * 2;
			elementtype temp = H->arr[parent];
			if (child + 1 <= H->nowsize&&H->arr[child + 1] >= H->arr[child])   //������ӽڵ���ڲ����ӽڵ�������ӽڵ�
				child++;													   //Ŀ������childָ�������ڵ�������Ǹ�
																			   //����Ķ�������������Ǹ��ڵ�����
			if (H->arr[parent] > H->arr[child])      //���������ӽڵ�Ļ���������һ��
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

//�ѵ����
void output(maxheap H)
{
	for (int i = 1; i <= H->nowsize; i++) {
		cout << H->arr[i] << "  ";
	}
	cout << endl;
}

//���ѵĲ���
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

//���ѵ�ɾ�����Ԫ��
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