#include<iostream>
using namespace std;


//˼·������������ʽ����
//����ʱ��Ҫ����arr1��arr3�����ֵ���ʼλ�ú���ֹλ��
//����arr1��    a1last�����һ��    a1chang-a1len�ǵ�һ��  a1chang�ǳ���  a1len���м�������
//ͬ��arr3Ҳ�����,a3last-a3len�ǵ�һ�����֣����պã�a3lenÿ�μ�һ���������ǰһλ��ûë��
//��ʱmarka����Ӽ���2
//�����ó�һλ��a3�����ֶ�һ��������a3len++��
//���arr1û�����ֵ��������У�i<��һ�����ּ�arr1û�������ˣ�����ֱ��a3last-a3len=M��a3len++����
//���arr1ָ��arr3��deletearr1��a1chang��a1len��a1last��Ҫ��a3����ȣ���Ϊֱ��ѭ��
//OK


int main()
{
	int M;
	int N;
	cout << "������M��" << endl;
	cin >> M;
	cout << "������N:" << endl;
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