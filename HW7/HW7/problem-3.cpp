#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<iomanip>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)

using namespace std;

class Map_Link
{
private:
	int n;
	int *fst;
	int *pre, *to, *val;
	int tot;

	void bfs(const int, bool* const) const;
	void dfs(const int, bool* const) const;
public:
	Map_Link();
	~Map_Link();
	Map_Link(const int, const int, const int);

	void add(const int, const int, const int, const int);

	void get_sc() const;
};
Map_Link::Map_Link()
{
	n = 0; tot = -1;
	fst = pre = val = NULL;
}
Map_Link::Map_Link(const int _n, const int m, const int mode)
{
	n = _n;
	fst = new(nothrow) int[n];
	pre = new(nothrow) int[m*(mode + 1)];
	val = new(nothrow) int[m*(mode + 1)];
	to = new(nothrow) int[m*(mode + 1)];
	if (fst == NULL || pre == NULL || val == NULL || to == NULL)
		exit(-1);
	sFor(i, 0, n)
		fst[i] = -1;
	tot = -1;
}
Map_Link::~Map_Link()
{
	if (fst != NULL)
		delete[]fst;
	if (pre != NULL)
		delete[]pre;
	if (val != NULL)
		delete[]val;
	if (to != NULL)
		delete[]to;
}

void Map_Link::add(const int u, const int v, const int w, const int mode)
{
	to[++tot] = v; pre[tot] = fst[u]; fst[u] = tot; val[tot] = w;
	if (mode)
	{
		to[++tot] = u; pre[tot] = fst[v]; fst[v] = tot; val[tot] = w;
	}
}

void Map_Link::get_sc() const
{
	bool *vis = new(nothrow) bool[n];
	if (vis == NULL)
		exit(-1);
	sFor(i, 0, n)
		vis[i] = 0;
	sFor(i, 0, n) if (!vis[i])
	{
		vis[i] = 1;
		cout << '{' << i;
		dfs(i, vis);
		cout << '}';
	}
	puts("");
	sFor(i, 0, n)
		vis[i] = 0;
	sFor(i, 0, n) if (!vis[i])
	{
		cout << '{' << i;
		bfs(i, vis);
		cout << '}';
	}
	puts("");
	delete[]vis;
}
void Map_Link::dfs(const int x, bool* const vis) const
{
	for (int k = fst[x]; k != -1; k = pre[k]) if (!vis[to[k]])
	{
		vis[to[k]] = 1;
		cout << ' ' << to[k];
		dfs(to[k], vis);
	}
}
void Map_Link::bfs(const int S, bool* const vis) const
{
	int *Q = new(nothrow) int[n];
	if (Q == NULL)
		exit(-1);
	int l = 0, r = 1; Q[l] = S; vis[S] = 1;
	while (l < r)
	{
		int u = Q[l++], base = n*u;

		for (int k = fst[u]; k != -1; k = pre[k]) if (!vis[to[k]])
		{
			Q[r++] = to[k];
			cout << ' ' << to[k];
			vis[to[k]] = 1;
		}
	}
	delete[]Q;
}

int main()
{
	int n, m;
	cin >> n >> m;
	Map_Link L(n, m, 1);

	For(i, 1, m)
	{
		int u, v;
		cin >> u >> v;
		L.add(u, v, 1, 1);
	}

	L.get_sc();

	system("pause");
	return 0;
}