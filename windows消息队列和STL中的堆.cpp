
//堆的STL使用在网站	http://blog.csdn.net/keshacookie/article/details/19612355
//重载需要在结构体内重载，在外面重载是没用的
//且重载函数的参数才是首选项，即不同于sort编写cmp时参数那个顺序


#include<iostream>
#include<queue>
#include<string>
#include<cstdio>
using namespace std;

struct message
{
	string name;
	int priority;
	bool operator<(const message&m2) const
	{
		return priority > m2.priority;
	}
};


typedef priority_queue<message> heap;

int main()
{
	int T;
	cin >> T;
	string receive;
	heap arr;
	for (int i = 0; i < T; i++)
	{
		char shit[10];
		scanf("%s", shit);
		receive = shit;
		if (receive == "GET")
		{
			if (arr.size() == 0)
				printf("EMPTY QUEUE!\n");
			else {
				printf("%s\n", arr.top().name.c_str());
				arr.pop();
			}
		}
		else if (receive == "PUT")
		{
			char tempname[10];
			string name;
			int priority;
			scanf("%s", tempname);
			scanf("%d", &priority);
			name = tempname;
			message temp;
			temp.name = name;
			temp.priority = priority;
			arr.push(temp);
		}
	}
	system("pause");
	return 0;
}