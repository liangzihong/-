#include<iostream>
#include<cctype>
using namespace std;
#define max 5000
int shuzi[max];
int shuzitop=0;
char fuhao[max];
int fuhaotop = 0;

/*���Ǹ�ֻ��������������������������ܼ򵥣�˼����ǰ���һ�����ŵ�shuzi���ջ�У��ڰ������һ�����ŵ�fuhao���ջ��
  Ȼ�����fuhaoջ���ҵ��˺ͳ��ģ���shuziջ�а�������������˺���������ѽ����Ϊshuzi��i����ֵ����һ������Ϊ0��
  fuhaoջ��ѳ˻�����ַ���ɿո�����ٱ�������ջ������Ӧ������ȫ����Ӽ��� */

void pushint(int a)
{
	shuzi[++shuzitop] = a;
}

void pushchar(char a)
{
	fuhao[++fuhaotop] = a;
}



int mark(void)
{
	char c;
	int arr = 1;
	int shu=0;
	c = cin.get();
	while (c != '='&&cin.fail()==false&&c!='\n')
	{
		if (c == '-')
		{
			arr = -1;
		}
		while (isdigit(c))
		{
			shu = shu * 10 + (int)c - 48;
			c = cin.get();
		}
		pushint(arr*shu);

		while (isspace(c))
		{
			c = cin.get();
		}
		if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			pushchar(c);
			c = cin.get();
		}
		else if (c == '=')
		{
			break;
		}
		else {
			cout << endl << "�Ƿ�����" << endl;
		}
		shu = 0;
		arr = 1;

	}
	if (cin.fail())
	{
		return 0;
	}
	else if (c == '\n')
	{
		cout << "��û����Ⱥţ��������" << endl;
		return 0;
	}
	else {
		cin.get();
		return 1;
	}
}


template <typename T>
void forward(T arr[], int n,int all)
{
	for (int i = n; i < all; i++)
	{
		arr[i] = arr[i + 1];
	}
}



int cal(void)
{
	int result=shuzi[1];
	for (int i = 1; i <= fuhaotop; i++)
	{
	
		if (fuhao[i] == '/')
		{
			shuzi[i] = shuzi[i] / shuzi[i + 1];
			shuzi[i + 1] = 0;
			fuhao[i] = ' ';
			forward(shuzi, i + 1, shuzitop--);
			forward(fuhao, i, fuhaotop--);
			i = 0;
		}	
		else if (fuhao[i] == '*')
		{
			shuzi[i] = shuzi[i] * shuzi[i + 1];
			shuzi[i + 1] = 0;
			fuhao[i] = ' ';
			forward(shuzi, i + 1, shuzitop--);
			forward(fuhao, i, fuhaotop--);
			i = 0;
		}
;
	}

	int cnt = 1;
	result = shuzi[1];
	for (int i = 1; i <= fuhaotop; i++)
	{
		if (fuhao[i] == '+')
		{
			result = result+ shuzi[++cnt];
 		}
		else if (fuhao[i] == '-')
		{
			result = result- shuzi[++cnt];
		}
		else if (fuhao[i] == ' ')
		{
			;
			cnt++;
		}
	}
	return result;
}


int main()
{
	while (mark())
	{
		cout << cal() << endl; 
		shuzitop = 0, fuhaotop = 0;
	}
}