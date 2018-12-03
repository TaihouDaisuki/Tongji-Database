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
public:
	Map_Matrix();
	~Map_Matrix();
	Map_Matrix(const int);

	void add(const int, const int, const int, const int);

	void output() const;
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
void Map_Matrix::add(const int u, const int v, const int w, const int mode)
{
	if (map == NULL)
		return;
	map[n*u + v] = w;
	if (mode)
		map[n*v + u] = w;
}
void Map_Matrix::output() const
{
	if (map == NULL)
		return;
	int N = n*n;
	For(i, 1, N)
	{
		cout << setw(4) << setiosflags(ios::right) << map[i - 1];
		if (!(i%n))
			puts("");
	}
}

class Map_Link
{
private:
	int n;
	int *fst;
	int *pre, *to, *val;
	int tot;
public:
	Map_Link();
	~Map_Link();
	Map_Link(const int, const int, const int);

	void add(const int, const int, const int, const int);

	void output(const char* const, const int) const;
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
void Map_Link::output(const char* const charmap, const int mode) const
{
	if (fst == NULL || pre == NULL || val == NULL || to == NULL)
		return;
	sFor(i, 0, n)
	{
		cout << charmap[i] << "-->";
		for (int k = fst[i]; k != -1; k = pre[k])
		{
			cout << to[k];
			if (mode)
				cout << ',' << val[k];
			cout << ' ';
		}
		puts("");
	}
}

int main()
{
	int mode;
	cin >> mode;
	int n, m;
	cin >> n >> m;
	Map_Matrix M(n);
	Map_Link L(n, m, mode > 2);

	char *charmap = new(nothrow) char[n];
	if (charmap == NULL)
		exit(-1);
	sFor(i, 0, n)
		cin >> charmap[i];
	For(i, 1, m)
	{
		char cu, cv;
		cin >> cu >> cv;
		int u, v;
		sFor(j, 0, n)
			if (charmap[j] == cu)
			{
				u = j;
				break;
			}
		sFor(j, 0, n)
			if (charmap[j] == cv)
			{
				v = j;
				break;
			}
		int w = 1;
		if (mode == 2 || mode == 4)
			cin >> w;
		M.add(u, v, w, mode > 2);
		L.add(u, v, w, mode > 2);
	}

	sFor(i, 0, n)
		cout << charmap[i] << ' ';
	puts("");
	M.output();
	L.output(charmap, !(mode & 1));

	system("pause");
	return 0;
}