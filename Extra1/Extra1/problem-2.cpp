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

using namespace std;

typedef int Status;
typedef struct Poly
{
	int p, e;
	bool operator ==(const Poly &rhs)const
	{
		return e == rhs.e;
	}
	bool operator >=(const Poly &rhs)const
	{
		return e >= rhs.e;
	}
	friend istream& operator >> (istream &, Poly &);
	friend ostream& operator << (ostream &, Poly &);
}ElemType;
istream& operator >> (istream &it, Poly &rhs)
{
	it >> rhs.p >> rhs.e;
	return it;
}
ostream& operator <<(ostream &it, Poly &rhs)
{
	it << rhs.p << ' ' << rhs.e << endl;
	return it;
}

class Linear_List
{
private:
	typedef struct LNode
	{
		ElemType data;
		LNode *pre;
		LNode *nxt;
	} LNode, *LinkList;
	LinkList L;

	void add(const ElemType); 
public:
	Linear_List();
	~Linear_List();

	Status output() const;

	Status insert(const ElemType);

	Status mul(const Linear_List &A, const Linear_List &B);
};

Linear_List::Linear_List()
{
	L = new(nothrow) LNode;
	if (L == NULL)
		exit(Overflow);
	L->pre = L->nxt = NULL;
}
Linear_List::~Linear_List()
{
	LinkList p = L, q;
	while (p != NULL)
		q = p->nxt, delete p, p = q;
}

Status Linear_List::output() const
{
	if (L->nxt == NULL)
	{
		puts("");
		return ERROR;
	}
	LinkList p = L->nxt;
	while (p != NULL)
		cout << p->data, p = p->nxt;
	return OK;
}

Status Linear_List::insert(const ElemType x)
{
	LinkList p = L;
	while (p->nxt != NULL)
	{
		if (p->nxt->data >= x)
			break;
		p = p->nxt;
	}
	LinkList q = new(nothrow) LNode;
	if (q == NULL)
		exit(Overflow);
	q->data = x;
	q->pre = p;
	q->nxt = p->nxt;
	if (p->nxt != NULL)
		p->nxt->pre = q;
	p->nxt = q;
	return OK;
}

Status Linear_List::mul(const Linear_List &A, const Linear_List &B)
{
	LNode *pA = A.L->nxt;
	while (pA != NULL)
	{
		LNode *pB = B.L->nxt;
		while (pB != NULL)
		{
			ElemType tmp = { 0,0 };
			tmp.e = pA->data.e + pB->data.e;
			tmp.p = pA->data.p*pB->data.p;
			add(tmp);
			pB = pB->nxt;
		}
		pA = pA->nxt;
	}
	return OK;
}
void Linear_List::add(const ElemType x)
{
	LinkList p = L;
	while (p->nxt != NULL)
	{
		if (p->nxt->data >= x)
			break;
		p = p->nxt;
	}
	if (p->nxt != NULL && p->nxt->data == x)
	{
		p->nxt->data.p += x.p;
		if (p->nxt->data.p)
			return;
		LinkList tmp = p->nxt;
		p->nxt = tmp->nxt;
		if (tmp->nxt != NULL)
			tmp->nxt->pre = p;
		return;
	}
	LinkList q = new(nothrow) LNode;
	if (q == NULL)
		exit(Overflow);
	q->data = x;
	q->pre = p;
	q->nxt = p->nxt;
	if (p->nxt != NULL)
		p->nxt->pre = q;
	p->nxt = q;
}

int main()
{
	Linear_List A, B;
	int n, m;
	cin >> m;
	For(i, 1, m)
	{
		ElemType x;
		cin >> x;
		A.insert(x);
	}
	cin >> n;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		B.insert(x);
	}

	Linear_List C;
	C.mul(A, B);
	C.output();

	//system("pause");
	return 0;
}
