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

	int bfs(const int) const;
public:
	Map_Link();
	~Map_Link();
	Map_Link(const int, const int, const int);

	void add(const int, const int, const int, const int);

	void calc() const;
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

void Map_Link::calc() const
{
	For(i, 1, n)
	{
		int ans = bfs(i);
		cout << i << ": ";
		double per = 100.0*ans / n;
		cout.setf(ios::fixed);
		cout << fixed << setprecision(2) << per << "%\n";
		cout.unsetf(ios::fixed);
	}
}
int Map_Link::bfs(const int S) const
{
	int *Q = new(nothrow) int[n];
	int *dep = new(nothrow) int[n + 1];
	if (Q == NULL || dep == NULL)
		exit(-1);
	For(i, 1, n)
		dep[i] = -1;
	int l = 0, r = 1, cnt = 1; 
	Q[l] = S; dep[S] = 0;
	while (l < r)
	{
		int u = Q[l++]; 
		if (dep[u] == 6)
			break;
		for (int k = fst[u]; k != -1; k = pre[k]) if (dep[to[k]] == -1)
		{
			Q[r++] = to[k];
			dep[to[k]] = dep[u] + 1;
			++cnt;
		}
	}
	delete[]dep;
	delete[]Q;
	return cnt;
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

	L.calc();

	//system("pause");
	return 0;
}