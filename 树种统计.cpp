#include<iostream>
#include<map>
#include<algorithm>
#include<iomanip>
#include<string>
using namespace std;

typedef pair<string, int> PAIR;
typedef map<string, int> MAP;

int T;
void output(PAIR arr)
{
	cout << arr.first << " ";
	cout << fixed;
	cout.precision(4);
	cout << double(arr.second)*100 / T <<"%"<< endl;
}
int main()
{
	cin >> T;
	cin.get();
	MAP treemap;
	for (int i = 0; i < T; i++)
	{
		string name;
		getline(cin, name);
		treemap[name]++;
	}
	for_each(treemap.begin(), treemap.end(), output);
	system("pause");
}