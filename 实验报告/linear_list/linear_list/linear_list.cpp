#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define Overflow 2

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

	Status del(const ElemType);
	Status del(const int, ElemType &);
	Status del_all(const ElemType);
	Status del_same();

	Status search(const ElemType, int &) const;
	Status reverse();
	Status output() const;

	/******************/
	/*only for ordered*/
	/******************/
	Status insert(const ElemType);
	Status Union(const Linear_List&, const Linear_List&);

	/********************/
	/*only for unordered*/
	/********************/
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

Status Linear_List::del(const ElemType x)
{
	LinkList p = L->nxt;
	while (p != NULL)
	{
		if (p->data == x)
		{
			p->pre->nxt = p->nxt;
			if (p != tail)
				p->nxt->pre = p->pre;
			else
				tail = p->pre;
			delete p;
			return OK;
		}
		p = p->nxt;
	}
	return ERROR;
}
Status Linear_List::del(const int i, ElemType &res)
{
	LinkList p = L->nxt;
	int pos = 1;
	while (p != NULL && pos < i)
		p = p->nxt, ++pos;
	if (p == NULL || pos > i)
		return ERROR;
	res = p->data;
	p->pre->nxt = p->nxt;
	if (p != tail)
		p->nxt->pre = p->pre;
	else
		tail = p->pre;
	delete p;
	return OK;
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
Status Linear_List::del_same()
{
	LinkList cur = L->nxt, p, q;
	while (cur != NULL)
	{
		p = cur->nxt;
		while (p != NULL)
		{
			q = p->nxt;
			if (p->data == cur->data)
			{
				p->pre->nxt = p->nxt;
				if (p != tail)
					p->nxt->pre = p->pre;
				else
					tail = p->pre;
				delete p;
			}
			p = q;
		}
		cur = cur->nxt;
	}
	return OK;
}

Status Linear_List::search(const ElemType x, int &pos) const
{
	LinkList p = L->nxt;
	pos = 1;
	while (p != NULL)
	{
		if (p->data == x)
			return OK;
		p = p->nxt, ++pos;
	}
	pos = -1;
	return ERROR;
}
Status Linear_List::reverse()
{
	if (tail == NULL)
		return ERROR;
	LinkList p = L->nxt, q = tail;
	ElemType tmp;
	while (p != q && p->pre != q)
	{
		tmp = p->data, p->data = q->data, q->data = tmp;
		p = p->nxt, q = q->pre;
	}
	return OK;
}
Status Linear_List::output() const
{
	cout << "=>";
	if (tail == L)
	{
		return ERROR;
	}
	LinkList p = L->nxt;
	while (p != tail)
		cout << p->data << "=>", p = p->nxt;
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


void unordered_test()
{
	Linear_List L;
	puts("/************************************/");
	puts("/*无序线性表的插入、删除、查找等测试*/");
	puts("/************************************/");
	puts("");
#define For(i,l,r) for(int i=l;i<=r;++i)
#define Pause while(_getch()!='\r')

	cout << "请输入初始数据个数 n = ";
	int n;
	cin >> n;
	cout << "请依次输入" << n << "个数字:" << endl;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		L.insert(i, x);
	}
	puts("输入的线性表建立如下"); L.output(); puts("");
	cout << "请按任意键继续..."; Pause; puts(""); puts("");

	if (1)
	{
		ElemType x; int pos; Status res;
		puts("/*线性表查找测试*/");
		cout << "请输入需要查找的数值 x = "; cin >> x;
		res = L.search(x, pos);
		if (res)
			cout << "查找到数值" << x << ",位置为第" << pos << "个\n";
		else
			cout << "查找失败，数值不存在" << endl;
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}

	if (1)
	{
		int pos; ElemType x;

		puts("/*头插测试，尝试在表头插入数据 1 */");
		L.insert(1, 1);
		puts("线性表的状态如下"); L.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");

		puts("/*尾插测试，尝试在表尾插入数据 -1 */");
		L.insert(L.length() + 1, -1);
		puts("线性表的状态如下"); L.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");

		puts("/*自定义插入测试*/");
		cout << "请输入希望插入的位置 pos 及数据 x : "; cin >> pos >> x;
		L.insert(pos, x);
		puts("线性表的状态如下"); L.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}

	if (1)
	{
		ElemType x; int pos; Status res;
		if (1)
		{
			puts("/*头删测试，尝试删除表头数据*/");
			res = L.del(1, x);
			if (res)
				cout << "删除成功，删除的数据为：" << x << endl;
			else
				cout << "删除失败，该位置不合法" << endl;
			puts("线性表的状态如下"); L.output(); puts("");
			cout << "请按任意键继续..."; Pause; puts(""); puts("");

			puts("/*尾删测试，尝试删除表尾数据*/");
			res = L.del(L.length(), x);
			if (res)
				cout << "删除成功，删除的数据为：" << x << endl;
			else
				cout << "删除失败，该位置不合法" << endl;
			puts("线性表的状态如下"); L.output(); puts("");
			cout << "请按任意键继续..."; Pause; puts(""); puts("");
		}
		if (1)
		{
			puts("/*自定义位置删除测试*/");
			cout << "请输入希望删除的位置 pos = "; cin >> pos;
			res = L.del(pos, x);
			if (res)
				cout << "删除成功，删除的数据为：" << x << endl;
			else
				cout << "删除失败，该位置不合法" << endl;
			puts("线性表的状态如下"); L.output(); puts("");
			cout << "请按任意键继续..."; Pause; puts(""); puts("");
		}
		if (1)
		{
			puts("/*自定义数值删除测试*/");
			cout << "请输入希望删除的数值 x = "; cin >> x;
			res = L.del(x);
			if (res)
				cout << "删除成功，删除的数据为：" << x << endl;
			else
				cout << "删除失败，该数值不存在" << endl;
			puts("线性表的状态如下"); L.output(); puts("");
			cout << "请按任意键继续..."; Pause; puts(""); puts("");
		}
	}

	if (1)
	{
		ElemType x; Status res;
		puts("/*删除所有值x测试*/");
		puts("当前线性表状态为"); L.output(); puts("");
		cout << "请输入需要全部删除的数值 x = "; cin >> x;
		res = L.del_all(x);
		if (res)
			puts("删除成功，当前线性表状态为"), L.output(), puts("");
		else
			puts("删除失败，该数值不存在");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");

		puts("/*去重测试*/");
		puts("当前线性表状态为"); L.output(); puts("");
		L.del_same();
		puts("去重后线性表状态为"); L.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}

	if (1)
	{
		puts("/*线性表的翻转测试*/");
		puts("当前线性表状态为"); L.output(); puts("");
		L.reverse();
		puts("对线性表翻转后，状态为"); L.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}
	puts(""); puts("");

	if (1)
	{
		puts("/*线性表的清空测试*/");
		puts("当前线性表状态为"); L.output(); puts("");
		L.clear();
		puts("对线性表清空后，状态为"); L.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}
	puts(""); puts("");
	puts("**************************************************");
	puts("*无序部分测试完毕，以下将对有序线性表进行特殊测试*");
	puts("**************************************************");
	cout << "请按任意键继续..."; Pause; puts(""); puts(""); puts(""); puts("");
}
void ordered_test()
{
	Linear_List LA, LB, LC;
	puts("/******************/");
	puts("/*有序线性表的测试*/");
	puts("/******************/");
	puts("");
	int n;

#define For(i,l,r) for(int i=l;i<=r;++i)
#define Pause while(_getch()!='\r')

	cout << "请输入线性表A初始数据个数 n = ";
	cin >> n;
	cout << "请依次输入" << n << "个非递减数字:" << endl;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		LA.insert(i, x);
	}
	puts("LA建立如下"); LA.output(); puts("");
	cout << "请按任意键继续..."; Pause; puts("");

	cout << "请输入线性表B初始数据个数 n = ";
	cin >> n;
	cout << "请依次输入" << n << "个非递减数字:" << endl;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		LB.insert(i, x);
	}
	puts("LB建立如下"); LB.output(); puts("");
	cout << "请按任意键继续..."; Pause; puts(""); puts("");

	if (1)
	{
		ElemType x;
		cout << "请对LA进行插入操作，输入一个想要插入的数值 x = "; cin >> x;
		LA.insert(x);
		puts("插入后LA的状态为"); LA.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}
	if (1)
	{
		puts("/*有序线性表合并测试*/");
		puts("LA状态如下"); LA.output(); puts("");
		puts("LB状态如下"); LB.output(); puts("");
		LC.Union(LA, LB);
		puts("有序合并LA、LB至LC后，LC状态如下"); LC.output(); puts("");
		cout << "请按任意键继续..."; Pause; puts(""); puts("");
	}

	puts(""); puts("");
	puts("**********************");
	puts("*有序特殊部分测试完毕*");
	puts("**********************");
	cout << "请按任意键继续..."; Pause; puts(""); puts(""); puts(""); puts("");
}

void test_part()
{
	if (1)
		unordered_test();
	if (1)
		ordered_test();
}

int main()
{
	/*test_part*/
	test_part();
	/***********/

	return 0;
}
