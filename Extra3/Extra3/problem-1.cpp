#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>

#define TRUE 1
#define FALSE 0
#define FULL -1
#define EMPTY -2
#define sFor(i,l,r) for(int i = l; i < r; ++i)
#define For(i,l,r) for(int i = l; i <= r; ++i)

using namespace std;

typedef string ElemType;
typedef int Status;

class Static_Link_List
{
private:
	struct Elem
	{
		ElemType data;
		int cur;
	};
	Elem *L;
	int size, len;
public:
	Static_Link_List();
	~Static_Link_List();

	int reset(const int);

	int get_tail() const;

	Status insert(const ElemType, const int);
	Status del(const int, ElemType &);

	int search(const ElemType) const;

	void output_status() const;
	void output_elem() const;
};

Static_Link_List::Static_Link_List()
{
	L = NULL;
}
Static_Link_List::~Static_Link_List()
{
	if (L != NULL)
		delete[]L;
}

int Static_Link_List::reset(const int _size)
{
	if (L != NULL)
		delete[]L;
	L = NULL; size = _size; len = 0;
	L = new(nothrow) Elem[size];
	if (L == NULL)
		exit(-1);
	sFor(i, 0, size)
		L[i].data = "N/A";
	L[0].cur = -1;
	sFor(i, 1, size - 1)
		L[i].cur = i + 1;
	L[size - 1].cur = -1;
	return TRUE;
}

int Static_Link_List::get_tail() const
{
	return len;
}

Status Static_Link_List::insert(const ElemType rhs, const int pos)
{
	if (L[1].cur == -1)
		return FULL;
	if (pos > len + 1 || pos < 1)
		return FALSE;
	int p = 0, cnt = 0;
	while (cnt < pos - 1)
		++cnt, p = L[p].cur;
	int q = L[1].cur;
	L[1].cur = L[q].cur; L[q].cur = L[p].cur; L[p].cur = q;
	L[q].data = rhs;
	++len;
	return TRUE;
}
Status Static_Link_List::del(const int pos, ElemType &res)
{
	if (L[0].cur == -1)
		return EMPTY;
	if (pos<1 || pos>len)
		return FALSE;
	int p = 0, cnt = 0;
	while (cnt < pos - 1)
		++cnt, p = L[p].cur;
	int q = L[1].cur, cur = L[p].cur;
	res = L[cur].data;
	L[p].cur = L[cur].cur; L[cur].cur = q; L[1].cur = cur;
	--len;
	return TRUE;
}

int Static_Link_List::search(const ElemType rhs) const
{
	int p = 0, res = 0;
	while (p != -1 && L[p].data != rhs)
		++res, p = L[p].cur;
	return p == -1 ? FALSE : res;
}

void Static_Link_List::output_status() const
{
	if (L == NULL)
		return;

	sFor(i, 0, size)
	{
		cout << i << " : " << L[i].data << " : " << L[i].cur;
		if (i % 3 == 2)
			puts("");
		else
			cout << "        ";
	}
	if (size % 3)
		puts("");
}
void Static_Link_List::output_elem() const
{
	int p = L[0].cur;
	while (p != -1)
	{
		cout << L[p].data << ' ';
		p = L[p].cur;
	}
	puts("");
}

int main()
{
	int m, n;
	cin >> m >> n;
	Static_Link_List L;
	L.reset(m);

	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		L.insert(x, i);
	}
	L.output_status();

	int pos; ElemType x;
	cin >> pos >> x;
	Status res = L.insert(x, pos);
	if (res == FULL)
		puts("FULL");
	else if (res == FALSE)
		puts("-1");
	else
		L.output_elem();

	cin >> pos;
	res = L.del(pos, x);
	if (res == EMPTY)
		puts("EMPTY");
	else if (res == FALSE)
		puts("-1");
	else
		cout << x << endl;

	ElemType y;
	cin >> y;
	pos = L.search(y);
	if (pos)
		cout << pos << endl;
	else
		puts("-1");

	cin >> x;
	res = L.insert(x, L.get_tail() + 1);
	if (res == FULL)
		puts("FULL");
	else
		L.output_elem();

	L.output_status();
	//system("pause");
	return 0;
}