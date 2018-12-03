#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)

using namespace std;

struct Node
{
	int child[2];
	char tag;
};


int main()
{
	int n;
	cin >> n;
	int m = 2 * n - 1;
	Node *T = new(nothrow) Node[m];
	int cnt = 1;
	T[0].child[0] = T[0].child[1] = m; T[0].tag = '*';
	char ch;
	string haff;
	For(i, 1, n)
	{
		ch = getchar();
		while (ch == '\n' || ch == '\r')
			ch = getchar();
		cin >> haff;
		int len = haff.length();
		int cur = 0;
		sFor(j, 0, len)
		{
			int tmp = haff[j] - '0';
			if (T[cur].child[tmp] == m)
			{
				T[cur].child[tmp] = cnt++;
				cur = T[cur].child[tmp];
				T[cur].child[0] = T[cur].child[1] = m;
				T[cur].tag = '*';
			}
			else
				cur = T[cur].child[tmp];
		}
		T[cur].tag = ch;
	}
	string code;
	cin >> code;
	int L = code.length();
	int l = 0;

	while (l < L)
	{
		int cur = 0;
		while (T[cur].tag == '*')
			cur = code[l++] == '0' ? T[cur].child[0] : T[cur].child[1];
		cout << T[cur].tag;
	}

	delete[]T;
	//system("pause");
	return 0;
}