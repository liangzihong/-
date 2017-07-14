#include<iostream>
using namespace std;


//思路：用数组做竖式运算
//做的时候要划清arr1和arr3有数字的起始位置和终止位置
//例如arr1中    a1last是最后一个    a1chang-a1len是第一个  a1chang是长度  a1len是有几个数字
//同理arr3也是如此,a3last-a3len是第一个数字，即刚好，a3len每次加一，数组就移前一位，没毛病
//此时marka代表加几个2
//得数得出一位，a3的数字多一个，所以a3len++；
//如果arr1没有数字但加数还有（i<第一个数字即arr1没有数字了），就直接a3last-a3len=M，a3len++即可
//最后arr1指向arr3，deletearr1，a1chang，a1len，a1last都要与a3的相等，因为直接循环
//OK


int main()
{
	int M;
	int N;
	cout << "请输入M：" << endl;
	cin >> M;
	cout << "请输入N:" << endl;
	cin >> N;
	if (N == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	int a = 1;


	int *arr1 = new int[1];
	int *arr3;
	a = 2;   arr1[0] = M;
	int a1len, a1chang, a1last;
	int a3len, a3chang, a3last;
	int marka, i;
	int deshu;
	int jinwei = 0;
	a1len = 1; a1chang = 1; a1last = 0;
	for (; a <= N; a++)
	{
		arr3 = new int[a + 2];
		a3len = 0;
		a3chang = a + 2;
		a3last = a + 1;
		i = a1last;

		for (marka = a; marka > 0; marka--)
		{

			if (i >= a1chang - a1len)
			{
				deshu = (arr1[i] + M + jinwei) % 10;
				arr3[a3last - a3len] = deshu;
				a3len++;
				jinwei = (arr1[i] + M + jinwei) / 10;
				i--;
			}

			else {
				arr3[a3last - a3len] = M + jinwei;
				jinwei = 0;
				a3len++;
			}
		}
		jinwei = 0;
		delete[]arr1;
		arr1 = arr3;
		a1chang = a3chang;
		a1last = a3last;
		a1len = a3len;
	}


	for (int i = a1chang - a1len; i <= a1last; i++)
	{
		cout << arr1[i];
	}

	system("pause");
	return 0;
}