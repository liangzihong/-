#include<iostream>
#include<stack>
#include<algorithm>
#include<list>
#include<string>
#include<iterator>
using namespace std;

stack<char> fuhao;

//��ʮ�ĵ���������·�Ϊ�Ĳ�
//1������   2���б�    3�����    4���������
//1������    �����õ��˵ݹ飬calculate�����������飬�����С��Ŀ����������
//����һ��ʼ�����ȶԵ�һ��Ԫ�������£�+-*/��ɨһ�飬�����õ��ݹ飬���� 2 3 10 10��24���Ϳ��Ա��2+23��2--22��2*12��
//���һ�����Ϳ��Ա�ɴӵڶ���Ԫ�ؿ�ʼ��23���ڶ���Ԫ�ؿ�ʼ��������-22��������ơ�
//��������Ҫ�õ�if  if�Ľṹ�� + - * /�����

//Ȼ��ڶ��������ҵݹ��ս��������ݹ���սᣬ������ȫ������ҵ�������ֻ��һ����ʱ����һ�����Ƿ����target���Ǿ�return true
//Ȼ�����+ - * /�����У���Ҫ���ǣ����������һ������ϱ���µ�����Ȼ���ֿ�ʼ����������������24��
//������  ��� 6 10 10    �� 5 10 10    -1 10 10���鶫����24������ơ�

//ע���ϸ���кܶ�
//�� n������==0������ֻҪ��=1����Ҫ�б�ݹ��ս�
//�� Ҫע��+-*/�У�/��%�б�ȡ��ͱ���������Ϊ0�� ���мǵ�Ҫ�÷������ջ�������Ⱥ�˳��push��ջ�С�
//�� ǰһ�����У��Ե���Ԫ��Ϊ�ս���+-*/���ݹ��targetҪ��������2 targetҪ���22��12�ȣ�������һ�����У��ݹ��target����24
//	��Ϊ��ʵ��ֻ���൱����һ���µ����飬ֻ��ͷ��Ԫ�غʹ�С��һ��
//�� ���ע����Ϊ�������������������׻��ԭ������޸ĵ�����������ٶ�̬��������飬��Ȼ������鷳


//2���б�
//������Ϊ�鷳��һ��������õ�һ������ջ��ԭ������㲻�ܵ�֪���������Ƚ�����һ�����������һ������Ҳ����ʽ�ӵ����ţ�
//������ֻ���뵽һ���취������ö�٣�  ��7�����
//�ֱ��ǣ���output���߸���������output�н����µķ����������������ͨ�����ö������޸�ʹ����������������ֶ�����һ��������˳��
//��  ��������������㣬����output�аѺ��������ֱ��һ����Ȼ�����ɾȥ��������

//�����õ���һ��indicate������������һ���������飬һ���������飬�����ո�����˳��������㣬��
//����������   6 2 6
//������       - *
//�����ᰴ˳��all=6-2��arr��1��=all=4��all=4*6=24���õ��ľ���24���Ϳ���return true��

//Ȼ�����return true����output�Ͼ�Ҫ�鷳���������ֶ��������˳��output����


//�ܵ�����main����������һ��next_permutation��������������ϣ������������24�������

//ע�⣬next_permutation��Ե����������return true��false����ֹ�����������ŵ��д�С����ʱֱ��return false
//����һ��ʼ�Ұ�6 5 3 1��5555�ǽ���ȥѭ������6 5 3 1���˳���ֲ��У�����ʵ6 3 5 1�ǿ��Ե�
//������һ��ʼ������sort����С�����ţ���֤һ������������϶���
//��5 5 5 5�����ȥ����˳����ֻ��һ�������ҿ���ֻ�����һ�����㼴��

bool calculate(int temp[], int n, int target)   //nΪ�������
{
	if (n <= 1) {
		if (target == *temp) return true;
		else return false;
	}
	int*arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = temp[i];
	}
	//+
	if (calculate(arr + 1, n - 1, target - *arr))
	{
		fuhao.push('+'); return true;
	}
	//-
	if (calculate(arr + 1, n - 1, *arr - target))
	{
		fuhao.push('-');
		return true;
	}
	//*
	if (*arr != 0 && target != 0 && target%*arr == 0) {
		if (calculate(arr + 1, n - 1, target / *arr))
		{
			fuhao.push('*');
			return true;
		}
	}
	// /
	if (*arr != 0 && target != 0 && *arr%target == 0) {
		if (calculate(arr + 1, n - 1, *arr / target))
		{
			fuhao.push('/'); return true;
		}
	}
	int mark1 = *arr;
	int mark2 = *(arr + 1);
	//ǰ�涼���У���Ҫ������һ�����
	//+
	*(arr + 1) = mark1 + mark2;
	if (calculate(arr + 1, n - 1, target)) {
		fuhao.push('+');
		return true;
	}


	//-
	*(arr + 1) = mark1 - mark2;
	if (calculate(arr + 1, n - 1, target)) {
		fuhao.push('-');
		return true;
	}

	//*
	*(arr + 1) = mark1 *mark2;
	if (calculate(arr + 1, n - 1, target)) {
		fuhao.push('*');
		return true;
	}
	// /
	if (mark1%mark2 == 0)
	{
		*(arr + 1) = mark1 / mark2;
		if (calculate(arr + 1, n - 1, target)) {
			fuhao.push('/');
			return true;
		}
	}

	*arr = mark1, *(arr + 1) = mark2;
	return false;
}

bool indicate(int arr[], int n, char arr2[])
{
	char*copyfuhao = new char[n - 1];
	for (int i = 0; i < n-1; i++) { 
		copyfuhao[i] = *(arr2 + i); 
	//	cout << copyfuhao[i] << endl;
	}
	int*temp = new int[n];

	for (int i = 0; i < n; i++) { 
		temp[i] = *(arr + i); 
	//	cout << temp[i] << endl;
	}
	int all = 0;
	int i = 0;
	for (; i < n - 1; i++)
	{
		switch (copyfuhao[i])
		{
		case '+':all = temp[i] + temp[i + 1]; temp[i + 1] = all; break;
		case '-':all = temp[i] - temp[i + 1]; temp[i + 1] = all; break;
		case '*':all = temp[i] * temp[i + 1]; temp[i + 1] = all; break;
		case '/':if (temp[i + 1] != 0) { all = temp[i] / temp[i + 1]; temp[i + 1] = all; break; }
		}
	}
	if (all == 24)return true;
	else return false;
}

void output(int arr[], int n)  
{
	int*temp = new int[n];
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i);  }
	char copyfuhao[100];
	char cf[100];
	int a = 0;
	while (fuhao.empty() == 0)
	{
		cf[a]=copyfuhao[a] = fuhao.top();
		a++;
		fuhao.pop();
	}
	int state = 0;
	//1���Ȱ�ǰ�������һ����ʣ�µİ�˳��
	switch (copyfuhao[0])
	{
	case '+':temp[0] = arr[0] + arr[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '-':temp[0] = arr[0] - arr[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '*':temp[0] = arr[0] * arr[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '/':temp[0] = arr[0] / arr[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	}
	copyfuhao[0] = copyfuhao[1]; copyfuhao[1] = copyfuhao[2];
	if (indicate(temp, 3, copyfuhao)) 
	{
		cout << "((" << arr[0] << cf[0] << arr[1] << ")" << cf[1] << arr[2]<<")" << cf[2 ] << arr[3];
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }
	//2���Ȱ��м��������һ����������˳��
	switch (copyfuhao[1])
	{
	case '+':temp[1] = arr[1] + arr[2]; temp[2] = temp[3]; break;
	case '-':temp[1] = arr[1] - arr[2]; temp[2] = temp[3]; break;
	case '*':temp[1] = arr[1] * arr[2]; temp[2] = temp[3]; break;
	case '/':temp[1] = arr[1] / arr[2]; temp[2] = temp[3]; break;
	}
	copyfuhao[1] = copyfuhao[2];
	if (indicate(temp, 3, copyfuhao)) 
	{ 
		cout << arr[0] << cf[0] << "(" << arr[1] << cf[1] << arr[2] << ")" << cf[2] << arr[3];
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }

	//3���ȰѺ����������һ����������˳��
	switch (copyfuhao[2])
	{
	case '+':temp[2] = arr[2] + arr[3]; break;
	case '-':temp[2] = arr[2] - arr[3];  break;
	case '*':temp[2] = arr[2] * arr[3]; break;
	case '/':temp[2] = arr[2] / arr[3]; break;
	}
	if (indicate(temp, 3, copyfuhao)) 
	{
		cout << arr[0] << cf[0] << arr[1] << cf[1] <<"("<< arr[2]<< cf[2] << arr[3]<<")";
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }

	//4���Ȱ��м�������һ�������������ٱ�һ��
	switch (copyfuhao[1])
	{
	case '+':temp[1] = arr[1] + arr[2]; temp[2] = temp[3]; break;
	case '-':temp[1] = arr[1] - arr[2]; temp[2] = temp[3]; break;
	case '*':temp[1] = arr[1] * arr[2]; temp[2] = temp[3]; break;
	case '/':temp[1] = arr[1] / arr[2]; temp[2] = temp[3]; break;
	}
	copyfuhao[1] = copyfuhao[2];
	switch (copyfuhao[1])
	{
	case '+':temp[1] = temp[1] + temp[2]; break;
	case '-':temp[1] = temp[1] - temp[2]; break;
	case '*':temp[1] = temp[1] * temp[2]; break;
	case '/':temp[1] = temp[1] / temp[2]; break;
	}
	if (indicate(temp, 2, copyfuhao))
	{
		cout << arr[0] << cf[0]<<"(" << "(" << arr[1] << cf[1] << arr[2] << ")" << cf[2] << arr[3] << ")";
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }

	//5 �ȰѺ���������һ�����ٰѺ���������һ��
	switch (copyfuhao[2])
	{
	case '+':temp[2] = arr[2] + arr[3]; break;
	case '-':temp[2] = arr[2] - arr[3];  break;
	case '*':temp[2] = arr[2] * arr[3]; break;
	case '/':temp[2] = arr[2] / arr[3]; break;
	}
	switch (copyfuhao[1])
	{
	case '+':temp[1] = temp[1] + temp[2]; break;
	case '-':temp[1] = temp[1] - temp[2]; break;
	case '*':temp[1] = temp[1] * temp[2]; break;
	case '/':temp[1] = temp[1] / temp[2]; break;
	}
	if (indicate(temp, 2, copyfuhao))
	{
		cout << arr[0] << cf[0] << "(" << arr[1] << cf[1] << "(" << arr[2] << cf[2] << arr[3] << "))";
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }

	//6  ���м�������һ����ǰ�������ٱ�һ��
	switch (copyfuhao[1])
	{
	case '+':temp[1] = arr[1] + arr[2]; temp[2] = temp[3]; break;
	case '-':temp[1] = arr[1] - arr[2]; temp[2] = temp[3]; break;
	case '*':temp[1] = arr[1] * arr[2]; temp[2] = temp[3]; break;
	case '/':temp[1] = arr[1] / arr[2]; temp[2] = temp[3]; break;
	}
	copyfuhao[1] = copyfuhao[2];


	switch (copyfuhao[0])
	{
	case '+':temp[0] = temp[0] + temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '-':temp[0] = temp[0] - temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '*':temp[0] = temp[0] * temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '/':temp[0] = temp[0] / temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	}
	copyfuhao[0] = copyfuhao[1];
	if (indicate(temp, 2, copyfuhao))
	{
		cout << "(" << arr[0] << cf[0] << "(" << arr[1] << cf[1] << arr[2] << "))" << cf[2] << arr[3];
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }


	//7  ǰ��������һ��������������һ��
	switch (copyfuhao[0])
	{
	case '+':temp[0] = temp[0] + temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '-':temp[0] = temp[0] - temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '*':temp[0] = temp[0] * temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	case '/':temp[0] = temp[0] / temp[1]; temp[1] = temp[2], temp[2] = temp[3]; break;
	}
	copyfuhao[0] = copyfuhao[1]; copyfuhao[1] = copyfuhao[2];
	switch (copyfuhao[1])
	{
	case '+':temp[1] = temp[1] + temp[2]; break;
	case '-':temp[1] = temp[1] - temp[2]; break;
	case '*':temp[1] = temp[1] * temp[2]; break;
	case '/':temp[1] = temp[1] / temp[2]; break;
	}
	if (indicate(temp, 2, copyfuhao))
	{
		cout << "(" << arr[0] << cf[0] << arr[1] << ")" << cf[1] << "(" << arr[2] << cf[2] << arr[3] << ")";
		cout << endl; return;
	}
	for (int i = 0; i < n; i++) { temp[i] = *(arr + i); }
	for (int i = 0; i < n - 1; i++) { copyfuhao[i] = cf[i]; }





















	/*while (i != n)
	{
		if ((ch2 == '-' || ch2 == '+') && (ch1 == '*' || ch1 == '/'))
		{
			ans.push_front('('); ans.push_back(')');
		}
		if (state == 1) {
			ans.push_back(ch1);
			ch1 = fuhao.top();
			fuhao.pop();
		}
		temp = to_string(arr[i++]);
		for (int j = 0; j < temp.size(); j++) {
			ans.push_back(temp[j]);
		}
		if (state == 1)
			ans.push_back(ch1);
		if (state == 0) {
			ans.push_back(ch1);
			state = 1;
		}
		temp = to_string(arr[i++]);
		for (int j = 0; j < temp.size(); j++) {
			ans.push_back(temp[j]);
		}
		if (fuhao.empty() == 0) {
			ch2 = ch1;
			ch1 = fuhao.top(), fuhao.pop();
		}
	}
	list<char>::iterator it = ans.begin();
	for (; it != ans.end(); it++) {
		cout << *it;
	}*/
}

int main()
{
	int state = 0;
	int isin = 0;
	const int N = 4;
	int arr[N];
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	sort(arr + 0, arr + N);
	while (next_permutation(arr + 0, arr + N))
	{
		isin = 1;
		if (calculate(arr, N, 24))
		{
			output(arr,N);
			state = 1;
			break;
		}
	} 
	if (isin == 0)
	{
		if (calculate(arr, N, 24)) {
			output(arr, N);
			state = 1;
		}
	}
	if (state == 0) cout << "���ܴճ�24��" << endl;
	system("pause");
}