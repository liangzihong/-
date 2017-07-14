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


//建立一个类，令它的数据都为public
//成员分别有数字a和指数power


//建立一个类的栈，
//开始进行找最小的质数
//找到了，如果栈为空或者质数不等于栈的前一个a，就添加类，它的a为那个质数，质数为1；
//如果等于栈的前一个a，就继续在那个对象里的power++；
//然后递归找下一个，继续如此操作；
//直至找出来的最小质数等于它本身；

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