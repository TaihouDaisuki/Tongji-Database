#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define Overflow 2

#define For(i,l,r) for(int i=l;i<=r;++i)
#define opFor(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

typedef int Status;
typedef int ElemType;

class Linear_List
{
private:
	typedef struct LNode
	{
		ElemType data;
		LNode *pre;
		LNode *nxt;
	} LNode, *LinkList;
	LinkList L, tail;
public:
	Linear_List();
	~Linear_List();

	Status clear();
	Status empty() const;
	int length() const;

	Status del_all(const ElemType);

	Status output() const;

	Status insert(const int, const ElemType);
};

Linear_List::Linear_List()
{
	L = new(nothrow) LNode;
	if (L == NULL)
		exit(Overflow);
	L->pre = L->nxt = NULL;
	tail = L;
}
Linear_List::~Linear_List()
{
	LinkList p = L, q;
	while (p != NULL)
		q = p->nxt, delete p, p = q;
	L = tail = NULL;
}

Status Linear_List::clear()
{
	LinkList p = L->nxt, q;
	while (p != NULL)
		q = p->nxt, delete p, p = q;
	L->nxt = L->pre = NULL;
	tail = L;
	return OK;
}
Status Linear_List::empty() const
{
	return tail == NULL;
}
int Linear_List::length() const
{
	LinkList p = L->nxt;
	int res = 0;
	while (p != NULL)
		++res, p = p->nxt;
	return res;
}

Status Linear_List::del_all(const ElemType x)
{
	LinkList p = L->nxt, q;
	Status exist = 0;
	while (p != NULL)
	{
		q = p->nxt;
		if (p->data == x)
		{
			p->pre->nxt = p->nxt;
			if (p != tail)
				p->nxt->pre = p->pre;
			else
				tail = p->pre;
			delete p;
			exist = 1;
		}
		p = q;
	}
	return exist;
}

Status Linear_List::output() const
{
	if (tail == L)
	{
		return ERROR;
	}
	LinkList p = L->nxt;
	while (p != tail)
		cout << p->data << " ", p = p->nxt;
	cout << p->data;
	return OK;
}


Status Linear_List::insert(const int i, const ElemType x)
{
	LinkList p = L;
	int pos = 0;
	while (p != NULL && pos < i - 1)
		p = p->nxt, ++pos;
	if (p == NULL || pos > i - 1)
		return ERROR;
	LinkList q = new(nothrow) LNode;
	if (q == NULL)
		exit(Overflow);
	q->data = x;
	q->pre = p;
	q->nxt = p->nxt;
	if (p == tail)
		tail = q;
	else
		p->nxt->pre = q;
	p->nxt = q;
	return OK;
}

const int Maxn = 1000010;
ElemType A[Maxn];

int main()
{
	Linear_List L;
	int n;
	cin >> n;
	For(i, 1, n)
		cin >> A[i];
	opFor(i, n, 1)
		L.insert(1, A[i]);

	ElemType x;
	cin >> x;
	Status res = L.del_all(x);
	if (!res)
		puts("-1");
	else
		L.output(), puts("");

	//system("pause");
	return 0;
}
