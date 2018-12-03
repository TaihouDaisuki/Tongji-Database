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
#define sFor(i,l,r) for(int i=l;i<r;++i)
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
	LinkList L;
public:
	Linear_List();
	~Linear_List();

	Status clear();
	Status empty() const;
	int length() const;

	Status del(const int, ElemType &);

	Status search(const ElemType, int &) const;;
	Status output() const;

	Status insert(const int, const ElemType);
	Status push(const int);
};

Linear_List::Linear_List()
{
	L = new(nothrow) LNode;
	if (L == NULL)
		exit(Overflow);
	L->pre = L->nxt = L;
}
Linear_List::~Linear_List()
{
	LinkList p = L->nxt, q;
	while (p != L)
		q = p->nxt, delete p, p = q;
	delete L;
	L = NULL;
}

Status Linear_List::clear()
{
	LinkList p = L->nxt, q;
	while (p != L)
		q = p->nxt, delete p, p = q;
	L->nxt = L->pre = L;
	return OK;
}
Status Linear_List::empty() const
{
	return L->nxt==L;
}
int Linear_List::length() const
{
	LinkList p = L->nxt;
	int res = 0;
	while (p != L)
		++res, p = p->nxt;
	return res;
}

Status Linear_List::del(const int i, ElemType &res)
{
	LinkList p = L->nxt;
	int pos = 1;
	while (p != L && pos < i)
		p = p->nxt, ++pos;
	if (p == L || pos > i)
		return ERROR;
	res = p->data;
	p->pre->nxt = p->nxt;
	p->nxt->pre = p->pre;
	delete p;
	return OK;
}

Status Linear_List::search(const ElemType x, int &pos) const
{
	LinkList p = L->nxt;
	pos = 1;
	while (p != L)
	{
		if (p->data == x)
			return OK;
		p = p->nxt, ++pos;
	}
	pos = -1;
	return ERROR;
}

Status Linear_List::output() const
{
	if (L->nxt==L)
		return ERROR;
	LinkList p = L->nxt;
	while (p->nxt!=L)
		cout << p->data << " ", p = p->nxt;
	cout << p->data;
	return OK;
}

Status Linear_List::insert(const int i, const ElemType x)
{
	LinkList p = L;
	int pos = 0;
	while (p->nxt != L && pos < i - 1)
		p = p->nxt, ++pos;
	if ((p == L && pos!=i-1) || pos > i - 1)
		return ERROR;
	LinkList q = new(nothrow) LNode;
	if (q == NULL)
		exit(Overflow);
	q->data = x;
	q->pre = p;
	q->nxt = p->nxt;
	p->nxt->pre=q;
	p->nxt = q;
	return OK;
}

Status Linear_List::push(const int x)
{
	LinkList p = new(nothrow) LNode;
	if (p == NULL)
		exit(Overflow);
	p->data = x;
	p->nxt = L;
	p->pre = L->pre;
	L->pre->nxt=p;
	L->pre = p;
	return OK;
}

int main()
{
	Linear_List L;
	int n;
	cin>>n;
	For(i,1,n)
	{
		ElemType x;
		cin>>x;
		L.push(x);
	}
	L.output(), puts("");

	int pos,x;
	cin>>pos>>x;
	Status res=L.insert(pos,x);
	if(res)
		L.output(), puts("");
	else
		puts("-1");

	cin>>pos;
	res=L.del(pos, x);
	if(res)
		L.output(), puts("");
	else
		puts("-1");

	cin>>x;
	res=L.search(x,pos);
	if(res)
		cout<<pos<<endl;
	else
		puts("-1");

	cout<<L.length()<<endl;

	//system("pause");
	return 0;
}
