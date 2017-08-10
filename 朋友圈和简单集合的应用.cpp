#include<iostream>
using namespace std;


/*
����Ϊֹ�ļ��϶��������飬�����÷���һ����֮ǰ�����Ǹ���ÿ��Ԫ�ض���һ���ṹ�壬�ṹ�������Լ���data������parent
Ȼ��ƾ��Ҳ���Եõ��Լ��ĸ��ڵ�����һ��


����β�ȡ�˲�ͬ�Ĵ�ʩ�����ǷǸ��ڵ㣬����ֵΪ�����ڵ����ţ������ڵ㣬����ֵ��Ϊ�����ڼ��ϵ�Ԫ�ظ�������������
��ÿ�μ��Ϻϲ��Ĳ�����ֻΪ���ڵ������������ڵ㲻��ͬ��˵�����ϲ�ͬ��Ȼ����ݴ�С���кϲ���
ֻ����һ������Ϳ���ʵ�ּ��ϵ���ء����Կ���



*/



#define max 30000
typedef int elementtype;
typedef int setmark;
typedef int set[max+1];    //���typedef�͹涨��setΪ  int set��300001��

//��ʼ���ܼ���
void initset(set arr,int n)
{
	for (int i = 1; i <=n; i++) {
		arr[i] = -1;
	}
}

//���������ڵ���Ϊ�����������Ϳ���ֻ�Ը��ڵ���д���С���Ϻϲ����󼯺ϣ���С���ϸ��ڵ��ֵ��arr[i]����Ϊ�󼯺ϸ��ڵ㣬��ʾ�Ǵ�ڵ���Ӽ�
//Ȼ��󼯺ϵĸ��ڵ��ֵ���Ϊ�ϲ��󼯺�Ԫ��
setmark setunion(setmark root1, setmark root2, set arr)
{
	if (arr[root1] < arr[root2])   //��Ϊ���ϵ�Ԫ���������෴�������Զ�С��0������ԽС����Խ��
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

setmark find(elementtype x, set arr)    //Ѱ�Ҽ��ϵĸ��ڵ㣬��Ϊ��arr��i���У�arr��i��С��0��Ϊ���ϸ��ڵ㣬����0�Ĳ��ǣ�
										//�����ڵ�Ķ���Ҳ�������һ���Ϳ����ˡ�������Ĭ�ϴ�ҳ�ʼ����-1ʱ����ѡ��һ����Ϊ���ϸ��ڵ�
{
	if (arr[x] < 0)
		return x;
	else {
		arr[x] = find(arr[x], arr);
		return arr[x];
	}
}

//����ÿһ�����ţ��������һ��ѧ�������ǰ����������������Ȧ���ϵĸ��ڵ�
//�����Ҷ����µģ�Ҳ���ǵ�һ������
//���Դ�ҵ�ֵ��Ϊ-1
//Ȼ���ҵĸ��ڵ�Ϊ1��2���������1��2��
//Ȼ������root��������Ȧ�ϲ�
//��1��Ϊ���ڵ㣬����arr[2]��ֵ��Ϊ��������Ϊ��������������ϣ���arr[1]��Ϊ-2����ʾ�����ڼ���������Ԫ��

//�����㷨�ǿ��Եģ����籾������������ 1 2 3 4��5 6 7 8
//�¼����������1 7
//��ô�ȶ�1̽�������ĸ��ڵ����1.  Ȼ���7̽�������ĸ��ڵ���5��
//Ȼ����������Ȧ���кϲ�����arr[5]��ֵ��Ϊ1����������

//��֮ǰ�������ɻ������6��7��8 ������벻�ˣ���ʵ��Ȼ����Ϊ���Բ���������Ը��ݸ��ڵ㡣
//�����ɻ�������һ��Ԫ�������������ţ���Ҫָ��������  ��ʵҲ��Ȼ����Ϊ��ÿһ��elementtype�������Ҹ��ڵ㣬ֻ�Ը��ڵ�������������Ҫ
void inputconnection(set arr)
{
	int cnt;
	elementtype first;
	cin >> cnt; cin >> first;
	setmark root1, root2;       //�������ڵ�
	root1 = find(first, arr);   //����firstԪ�����ڽ�ϵĸ��ڵ�����һ����Ȼ��ֱ�ӶԸ��ڵ���д�����������漰����
	for (int i = 1; i < cnt; i++)
	{
		elementtype other;
		cin >> other;
		root2 = find(other, arr);    //Ҳ��ÿһ��Ԫ�ض��ҵ�һ��ʼ�������ڼ��ϸ��ڵ�����һ�����ҵ��ͶԸ��ڵ���д���
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
	cout << "��" << m << "��" << endl;
	for (elementtype i = 1; i <= n; i++)
	{
		if (find(i, arr) == value || arr[i] == -m)      //ÿһ��Ԫ��׷����Դ�����Ƕ��٣����������Ǹ�
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