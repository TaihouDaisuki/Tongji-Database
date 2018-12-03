#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cctype>

using namespace std;

char op[1000];
int num[1000];
int opTop = 0, numTop = 0;
bool error = 0;

void calc()
{
	int y = num[--numTop];
	int x = num[--numTop];
	char opt = op[--opTop];
	int ans = 0;
	if (opt == '+')
		ans = x + y;
	else if (opt == '-')
		ans = x - y;
	else if (opt == '*')
		ans = x*y;
	else if (opt == '/')
	{
		if (!y)
		{
			error = 1;  return;
		}
		ans = x / y;
	}
	num[numTop++] = ans;
}

int main()
{
	char ch; ch = getchar();
	while (!error && (ch != '='))
	{
		if (isdigit(ch))
		{
			int x = ch - 48;
			while (isdigit(ch = getchar())) x = x * 10 + ch - 48;
			num[numTop++] = x;
			continue;
		}
		if (ch == '+' || ch == '-')
		{
			while (!error && opTop && op[opTop - 1] != '(')
				calc();
			op[opTop++] = ch;
		}
		else if (ch == '*' || ch == '/')
		{
			if (opTop && (op[opTop - 1] == '*' || op[opTop - 1] == '/'))
				calc();
			op[opTop++] = ch;
		}
		else if (ch == '(')
			op[opTop++] = ch;
		else if (ch == ')')
		{
			while (!error && op[opTop - 1] != '(')
			{
				if (!opTop)
				{
					error = 1; break;
				}
				calc();
			}
			--opTop;
		}
		else
			error = 1;
		ch = getchar();
	}
	while (!error && opTop)
		calc();
	if(error || numTop!=1)
		puts("ERROR");
	else
		cout << num[numTop - 1] << endl;
		
	//system("pause");
	return 0;
}
