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
	/*************/
	/*common part*/
	/*************/
	Linear_List();
	~Linear_List();

	Status clear();
	Status empty() const;
	int length() const;

	Status output() const;

	Status insert(const ElemType);
	Status Union(const Linear_List&, const Linear_List&);
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
	if (p == tail)
		tail = q;
	else
		p->nxt->pre = q;
	p->nxt = q;
	return OK;
}
Status Linear_List::Union(const Linear_List &A, const Linear_List &B)
{
	if (!empty())
		clear();
	LinkList p = A.L->nxt, q = B.L->nxt;
	LinkList tmp, cur;
	while (p != NULL)
	{
		if (p->data > q->data)
			tmp = p, p = q, q = tmp;
		cur = new(nothrow) LNode;
		if (cur == NULL)
			exit(Overflow);
		tail->nxt = cur, cur->pre = tail, cur->nxt = NULL;
		tail = cur;
		tail->data = p->data;
		p = p->nxt;
	}
	while (q != NULL)
	{
		cur = new(nothrow) LNode;
		if (cur == NULL)
			exit(Overflow);
		tail->nxt = cur, cur->pre = tail, cur->nxt = NULL;
		tail = cur;
		tail->data = q->data;
		q = q->nxt;
	}
	return OK;
}

int main()
{
	Linear_List LA,LB,LC;
	ElemType x;
	int LoveTaihouForever = 1;
	while(LoveTaihouForever)
	{
		cin>>x;
		if(!x)
			break;
		LA.insert(x);
	}
	while(LoveTaihouForever)
	{
		cin>>x;
		if(!x)
			break;
		LB.insert(x);
	}
	LC.Union(LA,LB);
	LC.output(); puts("");

	system("pause");
	return 0;
}
