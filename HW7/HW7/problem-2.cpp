#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<iomanip>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)

using namespace std;

class Map_Matrix
{
private:
	int *map;
	int n;

	void bfs(const int, bool* const) const;
	void dfs(const int, bool* const) const;
public:
	Map_Matrix();
	~Map_Matrix();
	Map_Matrix(const int);

	void add(const int, const int, const int);

	void get_sc() const;
};
Map_Matrix::Map_Matrix()
{
	n = 0; map = NULL;
}
Map_Matrix::Map_Matrix(const int _n)
{
	n = _n;
	int N = n*n;
	map = new(nothrow) int[N];
	if (map == NULL)
		exit(-1);
	sFor(i, 0, N)
		map[i] = 0;
}
Map_Matrix::~Map_Matrix()
{
	if (map != NULL)
		delete[]map;
}

void Map_Matrix::add(const int u, const int v, const int w)
{
	if (map == NULL)
		return;
	map[n*u + v] = w;
}

void Map_Matrix::get_sc() const
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
void Map_Matrix::dfs(const int x, bool* const vis) const
{
	int base = n*x;
	sFor(i, 0, n) if (map[base+i] && !vis[i])
	{
		vis[i] = 1;
		cout << ' ' << i;
		dfs(i, vis);
	}
}
void Map_Matrix::bfs(const int S, bool* const vis) const
{
	int *Q = new(nothrow) int[n];
	if (Q == NULL)
		exit(-1);
	int l = 0, r = 1; Q[l] = S; vis[S] = 1;
	while (l < r)
	{
		int u = Q[l++], base = n*u;
		
		sFor(i, 0, n) if (map[base + i] && !vis[i])
		{
			Q[r++] = i;
			cout << ' ' << i;
			vis[i] = 1;
		}
	}
	delete[]Q;
}

int main()
{
	int n, m;
	cin >> n >> m;
	Map_Matrix M(n);

	For(i, 1, m)
	{
		int u, v;
		cin >> u >> v;
		M.add(u, v, 1); M.add(v, u, 1);
	}

	M.get_sc();

	//system("pause");
	return 0;
}