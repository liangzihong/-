#include<iostream>
#include<cmath>
#define max 1000
using namespace std;


class Node
{
public:
	long int a;
	int power;
	Node()
	{
		a = 0;
		power = 1;
	}
	void print()
	{
		if (power != 1)
		{
			cout << a << "^" << power;
		}
		else
		{
			cout << a;
		}
	}
};

Node*arr = new Node[max];
int top;


//����һ���࣬���������ݶ�Ϊpublic
//��Ա�ֱ�������a��ָ��power


//����һ�����ջ��
//��ʼ��������С������
//�ҵ��ˣ����ջΪ�ջ�������������ջ��ǰһ��a��������࣬����aΪ�Ǹ�����������Ϊ1��
//�������ջ��ǰһ��a���ͼ������Ǹ��������power++��
//Ȼ��ݹ�����һ����������˲�����
//ֱ���ҳ�������С��������������

int isprime(int n)
{
	int prime = 1;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n%i == 0)
		{
			prime = 0;
			break;
		}
	}
	return prime;
}


int findmin(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n%i == 0&&isprime(i))
		{
			return i;
		}
	}
	return n;
}

void find(int n)
{
	int min = findmin(n);
	if (top==0)
	{
		arr[++top].a = min;
	}
	else if (min == arr[top].a)
	{
		arr[top].power++;
	}
	else
	{
		arr[++top].a = min;
	}
	if (min == n)
	{
		return;
	}
	find(n / min);
}




int main()
{
	int T;
	cin >> T;
	if (T == 1)
	{
		cout << "1=1" << endl;
	}
	else if (isprime(T))
	{
		cout << T << "=" << T << endl;
	}
	else
	{
		find(T);
		for (int i = 1; i <= top; i++)
		{
			arr[i].print();
			if (i != top)
			{
				cout << "*";
			}
		}
	}
	system("pause");
	return 0;
}