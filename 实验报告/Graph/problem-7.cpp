#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<iomanip>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)
#define opFor(i,r,l) for(int i=r; i>=l; --i)
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))

using namespace std;

class Map_Link
{
private:
	const int inf = 999999999 + 413;

	int n;
	int *(fst[2]);
	int *(pre[2]), *(to[2]), *val;
	int tot[2];
	int *ind, *oud;

	bool topo(const int *const, int *const, const int) const;
public:
	Map_Link();
	~Map_Link();
	Map_Link(const int, const int);

	void add(const int, const int, const int);

	void get_key_route() const;
};
Map_Link::Map_Link()
{
	n = 0; tot[0] = tot[1] = -1;
	fst[0] = fst[1] = NULL;
	pre[0] = pre[1] = NULL;
	val = NULL;
	to[0] = to[1] = NULL;
	ind = oud = NULL;
}
Map_Link::Map_Link(const int _n, const int m)
{
	n = _n; tot[0] = tot[1] = -1;
	fst[0] = new(nothrow) int[n + 1];
	fst[1] = new(nothrow) int[n + 1];
	ind = new(nothrow) int[n + 1];
	oud = new(nothrow) int[n + 1];
	pre[0] = new(nothrow) int[m];
	pre[1] = new(nothrow) int[m];
	val = new(nothrow) int[m];
	to[0] = new(nothrow) int[m];
	to[1] = new(nothrow) int[m];
	if (fst[0] == NULL || fst[1] == NULL ||
		pre[0] == NULL || pre[1] == NULL ||
		val == NULL ||
		to[0] == NULL || to[1] == NULL ||
		ind == NULL || oud == NULL)
		exit(-1);
	For(i, 1, n)
		fst[0][i] = fst[1][i] = -1, ind[i] = oud[i] = 0;
}
Map_Link::~Map_Link()
{
	if (fst[0] != NULL)
		delete[]fst[0];
	if (fst[1] != NULL)
		delete[]fst[1];
	if (pre[0] != NULL)
		delete[]pre[0];
	if (pre[1] != NULL)
		delete[]pre[1];
	if (val != NULL)
		delete[]val;
	if (to[0] != NULL)
		delete[]to[0];
	if (to[1] != NULL)
		delete[]to[1];
	if (ind != NULL)
		delete[]ind;
	if (oud != NULL)
		delete[]oud;
}

void Map_Link::add(const int u, const int v, const int w)
{
	to[0][++tot[0]] = v; pre[0][tot[0]] = fst[0][u]; fst[0][u] = tot[0]; val[tot[0]] = w;
	to[1][++tot[1]] = u; pre[1][tot[1]] = fst[1][v]; fst[1][v] = tot[1];
	++oud[u]; ++ind[v];
}

void Map_Link::get_key_route() const
{
	int *early = new(nothrow) int[n + 1];
	int *late = new(nothrow) int[n + 1];
	For(i, 1, n)
		early[i] = ind[i] ? -1 : 0;
	bool loop = topo(ind, early, 0);
	if (loop)
	{
		puts("0");
		delete[]early;
		delete[]late;
		return;
	}
	For(i, 1, n)
		late[i] = oud[i] ? inf : early[i];
	topo(oud, late, 1);
	int ans = -1;
	For(i, 1, n) if (!oud[i])
		ans = Max(ans, early[i]);
	cout << ans << endl;
	For(u, 1, n)
		for (int k = fst[0][u]; k != -1; k = pre[0][k])
		{
			int v = to[0][k];
			if (early[u] == late[v] - val[k])
				cout << u << "->" << v << endl;
		}
	delete[]early;
	delete[]late;
}
bool Map_Link::topo(const int *const _deg, int *const cost, const int f) const
{
	int *Q = new(nothrow) int[n];
	int *deg = new(nothrow) int[n + 1];
	int l = 0, r = 0, cnt = 0;
	For(i, 1, n)
		deg[i] = _deg[i];
	For(i, 1, n) if (!deg[i])
		Q[r++] = i;

	while (l < r)
	{
		int u = Q[l++]; ++cnt;
		for (int k = fst[f][u]; k != -1; k = pre[f][k])
		{
			int v = to[f][k];
			--deg[v];
			if (!f)
				cost[v] = Max(cost[v], cost[u] + val[k]);
			else
				cost[v] = Min(cost[v], cost[u] - val[k]);
			if (!deg[v])
				Q[r++] = v;
		}
	}

	delete[]deg;
	delete[]Q;
	return (cnt != n);
}

int main()
{
	int n, m;
	cin >> n >> m;
	Map_Link L(n, m);

	For(i, 1, m)
	{
		int u, v, w;
		cin >> u >> v >> w;
		L.add(u, v, w);
	}
	L.get_key_route();

	//system("pause");
	return 0;
}