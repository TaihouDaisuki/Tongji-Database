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
	const int inf = 999999999 + 413;

	int n;
	int *fst;
	int *pre, *to, *val;
	int tot;

public:
	Map_Link();
	~Map_Link();
	Map_Link(const int, const int, const int);

	void add(const int, const int, const int, const int);

	bool topo() const;
};
Map_Link::Map_Link()
{
	n = 0; tot = -1;
	fst = pre = val = NULL;
}
Map_Link::Map_Link(const int _n, const int m, const int mode)
{
	n = _n;
	fst = new(nothrow) int[n + 1];
	pre = new(nothrow) int[m*(mode + 1)];
	val = new(nothrow) int[m*(mode + 1)];
	to = new(nothrow) int[m*(mode + 1)];
	if (fst == NULL || pre == NULL || val == NULL || to == NULL)
		exit(-1);
	For(i, 1, n)
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

bool Map_Link::topo() const
{
	int *ind = new(nothrow) int[n + 1];
	int cnt = 0;
	For(i, 1, n)
		ind[i] = 0;
	For(u, 1, n)
		for (int k = fst[u]; k != -1; k = pre[k])
			++ind[to[k]];
	
	int *Q = new(nothrow) int[n];
	int l = 0, r = 0;
	For(i, 1, n) if (!ind[i])
		Q[r++] = i;
	while (l < r)
	{
		int u = Q[l++]; ++cnt;
		for (int k = fst[u]; k != -1; k = pre[k])
		{
			int v = to[k];
			--ind[v];
			if (!ind[v])
				Q[r++] = v;
		}
	}
	
	delete[]ind;
	delete[]Q;
	return (cnt == n);
}

int main()
{
	int n, m;
	cin >> n >> m;
	Map_Link L(n, m, 0);

	For(i, 1, m)
	{
		int u, v, w;
		cin >> u >> v >> w;
		L.add(u, v, w, 0);
	}
	bool loop = L.topo();
	cout << loop << endl;

	//system("pause");
	return 0;
}