#include<iostream>
#include<stack>
using namespace std; 


typedef struct
{
	char start;
	char temp;
	char end;
	int cnt;
}tower;


int main()
{
	stack<tower> arr;
	int all;
	tower a;
	a.start = 'a', a.temp = 'b', a.end = 'c';
	cin >> all;
	a.cnt = all;
	arr.push(a);
	while (arr.empty() == 0)
	{
		a = arr.top();
		arr.pop();
		if (a.cnt == 1) cout << a.start << " -> " << a.end << endl;
		else
		{
			tower temp;
			temp.cnt = a.cnt - 1, temp.start = a.temp;
			temp.temp = a.start, temp.end = a.end;
			arr.push(temp);
			temp = a; temp.cnt =1;
			arr.push(temp);
			temp.cnt = a.cnt - 1, temp.start = a.start;
			temp.temp = a.end, temp.end = a.temp;
			arr.push(temp);
		}
	}
	system("pause");
	return 0;
}