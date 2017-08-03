#include<iostream>
#include<stack>
#include<string>
#include<cctype>
using namespace std;

typedef struct
{
	char ch;
	int level;
}node;

//这里要求的是   栈里的符号输出来有两个条件，第一个就是进来的符号（不含‘（’和‘）’）比栈顶的优先级低。
										// 	第二个就是没有符号再进来，就逐个逐个pop
//而数字则是遇到就输出


int main()
{
	int relerant=1;
	int cnt = 0;
	stack<node> arr;
	char ch;
	char form;
	string temp;
	double num;
	int state = 0;
	node target;
	ch = cin.get();
	form = ch;
	while (ch != '\n')
	{
		cnt++;
		temp = "";
		state = 0;
		while (isdigit(ch)||ch=='.')
		{
			if (form == '-'&&relerant==1)
				temp += form;
			temp += ch;
			state = 1;
			form = ch;
			ch = cin.get();
		}
		if (state == 1)
		{
			num = stod(temp);
			cout << num << " ";
		}
		else
		{
			switch (ch)
			{
			case ')':
				target.ch = ch;
				target.level = 0;
				break;
			case '(':
				target.ch = ch;
				target.level = 0;
				break;
			case '*':
				target.ch = ch;
				target.level = 3;
				break;
			case '/':
				target.ch = ch;
				target.level = 3;
				break;
			case '-':
				if (form == '(' || cnt == 1)
				{
					relerant = 1;
					goto end;
				}
				relerant = 0;
				target.ch = ch;
				target.level = 1;
				break;
			case '+':
				if (form == '('||cnt==1)
					goto end;
				target.ch = ch;
				target.level = 1;
				break;
			}
			if (arr.empty() ==1)
				arr.push(target);
			else
			{
					if (ch != '('&&ch != ')')
					{
						while (arr.top().level >= target.level)
							//进来的符号优先级低或同级,要一直输出，直至空了
						{
							cout << arr.top().ch << " ";
							arr.pop();
							if (arr.size() == 0|| arr.top().level < target.level)
							{
								arr.push(target);
								break;
							}
						}
						if (arr.top().level < target.level)      //进来的符号优先级高
						{
							arr.push(target);
						}
					}

					if (ch == '(')
					{
						arr.push(target);
					}
					if (ch == ')')
					{
						while (arr.top().ch != '(')
						{
							cout << arr.top().ch << " ";
							arr.pop();
						}
						arr.pop();
					}

			}
			end:
			form = ch;
			ch = cin.get();
		}
	}
	while (arr.empty() == 0)
	{
		cout << arr.top().ch << " ";
		arr.pop();
	}
	system("pause");
	return 0;
}