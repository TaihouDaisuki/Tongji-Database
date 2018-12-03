#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>

#define For(i,l,r) for(int i = l; i <= r; ++i)
#define sFor(i,l,r) for(int i = l; i < r; ++i)
#define opFor(i,r,l) for(int i = r; i >= l; --i)

using namespace std;

struct Position
{
	int pos, dev;
	Position() {};
	Position(int _pos, int _dev) { pos = _pos; dev = _dev; }
};

class HashTable
{
private:
	const int key = 37;
	int p, n;
	struct Table
	{
		string S;
		int Id;
		Table() {};
		Table(string _S, int _Id) { S = _S; Id = _Id; }
	};
	Table *hash;
public:
	HashTable();
	~HashTable();
	HashTable(const int, const int = 2);

	Position add(const string, const int = -1);
};

HashTable::HashTable()
{
	n = 0; p = 2;
	hash = NULL;
}
HashTable::~HashTable()
{
	if (hash != NULL)
		delete[]hash;
	hash = NULL;
}
HashTable::HashTable(const int _n, const int _p)
{
	n = _n; p = _p;
	hash = new(nothrow) Table[p];
	if (hash == NULL)
		exit(-1);
	sFor(i, 0, p)
		hash[i].Id = -1;
}

Position HashTable::add(const string S, const int Id)
{
	int len = S.length();
	int temp = 1, thash = 0;
	opFor(i, len - 1, 0)
	{
		thash += (int(S[i]) * temp) % p;
		if (thash >= p)
			thash -= p;
		temp *= key;
		temp %= p;
	}
	const int st = thash;
	int dev = 1;
	while (hash[thash].Id != -1)
	{
		++thash; ++dev;
		if (thash == p)
			thash = 0;
		if (thash == st)
			return Position(-1, 0);
	}
	hash[thash] = Table(S, Id);
	return Position(thash, dev);
}

int main()
{
	int n, p;
	cin >> n >> p;
	HashTable hash(n, p);
	Position *pos = new(nothrow) Position[n];
	if (pos == NULL)
		exit(-1);

	string Name;
	sFor(i, 0, n)
	{
		cin >> Name;
		pos[i] = hash.add(Name, i);
	}
	sFor(i, 0, n)
		cout << pos[i].pos << ' ';
	puts("");
	sFor(i, 0, n)
		cout << pos[i].dev << ' ';
	puts("");
	delete[]pos;

	system("pause");
	return 0;
}