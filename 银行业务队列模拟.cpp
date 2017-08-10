#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

typedef deque<int> ARR;
int main()
{
	ARR arra;
	ARR arrb;
	ARR ans;
	int cnt;
	cin >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		int temp;
		cin >> temp;
		if (temp % 2)   //ÆæÊý
			arra.push_back(temp);
		else
			arrb.push_back(temp);
	}
	while (cnt-- > 0)
	{
		if(arra.size()!=0)
		{
			ans.push_back(arra.front());
			arra.pop_front();
		}	
		if (arra.size() != 0)
		{
			ans.push_back(arra.front());
			arra.pop_front();
		}
		if (arrb.size() != 0)
		{
			ans.push_back(arrb.front());
			arrb.pop_front();
		}
	}

	while (ans.size() != 0)
	{
		cout << ans.front();
		ans.pop_front();
		if (ans.size() != 0)
			cout << " ";
	}
	system("pause");
	return 0;
}