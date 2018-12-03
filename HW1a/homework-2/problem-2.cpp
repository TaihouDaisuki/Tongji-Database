#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)
#define opFor(i,r,l) for(int i=r; i>=l; --i)
#define OK 1
#define ERROR 0
#define START_LENGTH 1000010
#define NEW_LENGTH 10
#define Lazy 2147483647

using namespace std;

typedef int ElemType;
typedef int Statue;

class SQList
{
private:
	struct LinkList
	{
		ElemType *elem;
		int length, tail;
	} L;
	void ReNew_L()
	{
		ElemType *New = new(nothrow) ElemType[L.length + NEW_LENGTH];
		if (New == NULL)
		{
			puts("No more free memory");
			exit(-1);
		}
		memcpy(New, L.elem, L.length * sizeof(ElemType));
		delete[]L.elem;
		L.elem = New;
		L.length += NEW_LENGTH;
	}
public:
	SQList();
	~SQList();
	void add(const ElemType);
	void del_rep();
	void output();
};

SQList::SQList()
{
	L.length = START_LENGTH;
	L.tail = 0;
	L.elem = new(nothrow) ElemType[L.length];
	if (L.elem == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
}

SQList::~SQList()
{
	delete[]L.elem;
}

void SQList::add(const ElemType x)
{
	if (L.length == L.tail)
		ReNew_L();
	L.elem[L.tail++] = x;
}

void SQList::del_rep()
{
	const int Maxa = 10000;
	bool f[Maxa + 10];
	For(i, 0, Maxa)
		f[i] = 0;
	sFor(i, 0, L.tail)
		if (!f[L.elem[i]])
			f[L.elem[i]] = 1;
		else
			L.elem[i] = Lazy;
	int l = 0, r = 1;
	while (L.elem[l] != Lazy) ++l, ++r;
	while (r < L.tail)
	{
		while (L.elem[r] != Lazy && r < L.tail)
			L.elem[l++] = L.elem[r++];
		++r;
	}
	L.tail = l;
}

void SQList::output()
{
	if (!L.tail)
		puts("");
	sFor(i, 0, L.tail - 1)
		printf("%d ", L.elem[i]);
	printf("%d\n", L.elem[L.tail - 1]);
}

int main()
{
	SQList List;

	int n;
	scanf(" %d", &n);
	For(i, 1, n)
	{
		int x;
		scanf(" %d", &x);
		List.add(x);
	}

	List.del_rep();
	List.output();

	//system("pause");
	return 0;
}