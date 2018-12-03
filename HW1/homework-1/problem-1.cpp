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
#define START_LENGTH 100
#define NEW_LENGTH 10

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
	Statue add(const ElemType, const int);
	Statue del(const int);
	int search(const ElemType);
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

Statue SQList::add(const ElemType x, const int pos)
{
	if (pos<1 || pos>L.tail + 1)
		return ERROR;
	if (L.length == L.tail)
		ReNew_L();
	opFor(i, L.tail - 1, pos - 1)
		L.elem[i + 1] = L.elem[i];
	L.elem[pos - 1] = x;
	++L.tail;
	return OK;
}

Statue SQList::del(const int pos)
{
	if (pos<1 || pos>L.tail)
		return ERROR;
	sFor(i, pos - 1, L.tail - 1)
		L.elem[i] = L.elem[i + 1];
	--L.tail;
	return OK;
}

int SQList::search(const ElemType x)
{
	sFor(i, 0, L.tail)
		if (L.elem[i] == x)
			return i + 1;
	return -1;
}

void SQList::output()
{
	if (!L.tail)
	{
		puts("");
		return;
	}
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
	List.output();

	int i, x;
	Statue res;
	scanf(" %d %d", &i, &x);
	res = List.add(x, i);
	if (res)
		List.output();
	else
		puts("-1");

	scanf(" %d", &i);
	res = List.del(i);
	if (res)
		List.output();
	else
		puts("-1");

	scanf(" %d", &x);
	int pos = List.search(x);
	printf("%d\n", pos);

	//system("pause");
	return 0;
}