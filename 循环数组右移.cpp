#include<iostream>
using namespace std;

int main()
{
	int N;
	int M;
	cin >> N >> M;
	int *arr1 = new int[N];
	M = M%N;

	int *arr2 = new int[N];

	for (int i = 0; i < N; i++)
	{
		cin >> arr1[i];
	}

	int cnt = 0;
	for (int i = N - 1 - M + 1; i < N; i++)
	{
		arr2[cnt++] = arr1[i];
	}
	for (int i = 0; i < N - 1 - M + 1; i++)
	{
		arr2[cnt++] = arr1[i];
	}

	cout << arr2[0];
	for (int i = 1; i < N; i++)
	{
		cout << " " << arr2[i];
	}

	delete[]arr1;
	delete[]arr2;
	system("pause");

}