#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<iomanip>
#include<algorithm>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)

using namespace std;

struct Edge
{
	int u, v;
	int w;

	bool operator <(const Edge &rhs) const
	{
		return w < rhs.w;
	}

	Edge() {}
	Edge(const int _u, const int _v, const int _w)
	{
		u = _u; v = _v; w = _w;
	}
};

inline int getfa(int* const fa, const int x)
{
	return (fa[x] == x) ? (fa[x]) : (fa[x] = getfa(fa, fa[x]));
}
void Kruskal(Edge* E, const int n, const int m)
{
	int *fa = new(nothrow) int[n + 1];
	if (fa == NULL)
		exit(-1);
	For(i, 1, n)
		fa[i] = i;

	sort(E, E+m);

	int ans = 0, cnt = 0;
	sFor(i, 0, m)
	{
		int u = getfa(fa, E[i].u), v = getfa(fa, E[i].v);
		if (u == v)
			continue;
		ans += E[i].w; fa[u] = v; ++cnt;
		if (cnt == n - 1)
			break;
	}
	if (cnt == n - 1)
		cout << ans << endl;
	else
		puts("-1");

	delete[]fa;
}

int main()
{
	int n, m;
	cin >> n >> m;
	Edge *E = new(nothrow) Edge[m];
	if (E == NULL)
		exit(-1);

	sFor(i, 0, m)
	{
		int u, v, w;
		cin >> u >> v >> w;
		E[i] = Edge(u, v, w);
	}

	Kruskal(E, n, m);
	delete[]E;

	system("pause");
	return 0;
}