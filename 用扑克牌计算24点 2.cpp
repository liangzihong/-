#include<iostream>
#include<stack>
#include<algorithm>
#include<list>
#include<string>
#include<iterator>
using namespace std;

stack<char> fuhao;

//二十四点计算程序大致分为四步
//1、计算   2、判别    3、输出    4、排列组合
//1、计算    计算用到了递归，calculate函数接受数组，数组大小和目标三个参数
//函数一开始，首先对第一个元素下文章，+-*/各扫一遍，这里用到递归，比如 2 3 10 10找24，就可以变成2+23，2--22，2*12等
//如此一来，就可以变成从第二个元素开始找23，第二个元素开始的数组找-22等如此类推。
//不过这里要用到if  if的结构， + - * /分清楚

//然后第二步就是找递归终结条件，递归的终结，可以完全归咎于找到当数组只有一个数时，这一个数是否就是target。是就return true
//然后如果+ - * /都不行，就要考虑，这个数于下一个数结合变成新的数，然后又开始以三个数的数组找24。
//如这里  变成 6 10 10    ， 5 10 10    -1 10 10三组东西找24如此类推。

//注意的细节有很多
//① n还可能==0，所以只要《=1，就要判别递归终结
//② 要注意+-*/中，/和%中被取余和被除数不能为0； 还有记得要用符号这个栈，来按先后顺序push进栈中。
//③ 前一部分中，以单个元素为终结点的+-*/，递归的target要做处理，如2 target要变成22，12等，而在下一部分中，递归的target则是24
//	因为其实这只是相当于有一个新的数组，只是头个元素和大小不一样
//④ 最后注意因为是数组做参数，很容易会把原数组给修改掉，所以最好再动态分配个数组，虽然这个很麻烦


//2、判别
//这是最为麻烦的一步，当你得到一个符号栈和原数组后，你不能得知三个符号先进行哪一个，后进行哪一个，（也就是式子的括号）
//所以我只能想到一个办法，就是枚举，  有7种情况
//分别是，见output的七个方法。在output中建立新的符号数组和数字数组通过逐个枚举逐个修改使符号数组和数字数字都按照一定的运算顺序
//如  把最后两个先运算，则在output中把后两个数字变成一个，然后符号删去这种类型

//这里用到了一个indicate函数，它接受一个数字数组，一个符号数组，它按照给定的顺序进行运算，如
//数字数组是   6 2 6
//符号是       - *
//则它会按顺序，all=6-2，arr【1】=all=4，all=4*6=24；得到的就是24，就可以return true了

//然后如果return true，在output上就要麻烦的逐个逐个手动按照你的顺序output括号


//总的则在main函数里面来一个next_permutation函数来个排列组合，这样就完成了24点的运算

//注意，next_permutation针对的排列组合是return true和false，终止条件是数组排到有大到小，此时直接return false
//所以一开始我按6 5 3 1和5555是进不去循环，而6 5 3 1这个顺序又不行，但其实6 3 5 1是可以的
//所以我一开始就来个sort，从小到大排，保证一定可以所有组合都来
//而5 5 5 5则进不去，但顺序又只有一个，那我可以只针对这一个来搞即可

bool calculate(int temp[], int n, int target)   //n为数组个数
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
	//前面都不行，就要与后面的一个结合
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
	//1、先把前两个变成一个，剩下的按顺序
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
	//2、先把中间的两个变一个，其他按顺序
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

	//3、先把后面的两个变一个，其他按顺序
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

	//4、先把中间两个变一个，后面两个再变一个
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

	//5 先把后面两个变一个，再把后面两个变一个
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

	//6  把中间两个变一个，前面两个再变一个
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


	//7  前面两个变一个，后面两个变一个
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
	if (state == 0) cout << "不能凑成24点" << endl;
	system("pause");
}