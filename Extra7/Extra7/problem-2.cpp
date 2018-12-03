#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)
#define opFor(i,r,l) for(int i=r; i>=l; --i)

using namespace std;

struct Node
{
	int ch[2], fa;
	int w;
};

int main()
{
	int n, root;
	cin >> n;
	Node *T = new(nothrow) Node[2 * n];
	For(i, 1, 2 * n - 1)
	{
		int w, p, l;
		cin >> w >> p >> l;
		if (!p)
			root = i;
		T[i].w = w, T[i].fa = p, T[p].ch[l] = i;
	}

	string route;
	For(i, 1, n)
	{
		int cur = T[i].fa, pre=i;
		route = "";
		while (cur != 0)
			route += T[cur].ch[0] == pre ? "0" : "1", cur = T[cur].fa, pre = T[pre].fa;
		cout << i << ' ';
		int len = route.length();
		opFor(j, len - 1, 0)
			cout << char(route[j]);
		puts("");
	}

	delete[]T;
	//system("pause");
	return 0;
}