#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<iomanip>
#include<queue>

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

	struct Heap
	{
		int x, dis;
		Heap() {}
		Heap(const int _x, const int _dis) { x = _x; dis = _dis; }

		bool operator <(const Heap &rhs) const
		{
			return dis > rhs.dis;
		}
	};
	
public:
	Map_Link();
	~Map_Link();
	Map_Link(const int, const int, const int);

	void add(const int, const int, const int, const int);

	void bellman_ford(const int) const;
	void dijkstra(const int) const;
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

void Map_Link::bellman_ford(const int S) const
{
	int* dis = new(nothrow) int[n + 1];
	bool* vis = new(nothrow) bool[n + 1];
	if (dis == NULL || vis == NULL)
		exit(-1);
	For(i, 1, n)
		dis[i] = inf, vis[i] = 0;
	
	deque<int> Q;
	Q.push_back(S);
	vis[S] = 1; dis[S] = 0;
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop_front(); vis[u] = 0;
		for (int k = fst[u]; k != -1; k = pre[k])
		{
			int v = to[k];
			if (dis[v] <= dis[u] + val[k])
				continue;
			dis[v] = dis[u] + val[k];
			if (vis[v])
				continue;
			if (!Q.empty() && dis[v] < dis[Q.front()])
				Q.push_front(v);
			else
				Q.push_back(v);
			vis[v] = 1;
		}
	}

	For(i, 1, n)
		cout << (dis[i] == inf ? 2147483647 : dis[i]) << ' ';
	puts("");

	delete[]vis;
	delete[]dis;
}
void Map_Link::dijkstra(const int S) const
{
	int* dis = new(nothrow) int[n + 1];
	bool* vis = new(nothrow) bool[n + 1];
	if (dis == NULL || vis == NULL)
		exit(-1);
	For(i, 1, n)
		dis[i] = inf, vis[i] = 0;

	priority_queue<Heap> H;
	H.push(Heap(S, 0)); dis[S] = 0;
	while (!H.empty())
	{
		Heap u = H.top(); H.pop();
		if (dis[u.x] != u.dis)
			continue;
		vis[u.x] = 1;
		for (int k = fst[u.x]; k != -1; k = pre[k])
		{
			int v = to[k];
			if (vis[v] || dis[v] <= u.dis + val[k])
				continue;
			dis[v] = u.dis + val[k];
			H.push(Heap(v, dis[v]));
		}
	}

	For(i, 1, n)
		cout << (dis[i] == inf ? 2147483647 : dis[i]) << ' ';
	puts("");

	delete[]vis;
	delete[]dis;
}

int main()
{
	int n, m, S;
	cin >> n >> m >> S;
	Map_Link L(n, m, 0);

	For(i, 1, m)
	{
		int u, v, w;
		cin >> u >> v >> w;
		L.add(u, v, w, 0);
	}

	L.bellman_ford(S);
	//L.dijkstra(S);

	//system("pause");
	return 0;
}