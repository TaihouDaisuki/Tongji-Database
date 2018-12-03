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
#define Initial_L 10 /////////////////////////
#define Block_L 10

using namespace std;

typedef int Status;
typedef int ElemType;

class SQList
{
private:
#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)
#define opFor(i,r,l) for(int i=r;i>=l;--i)
	const ElemType Lazy = 2147483647;

	struct LinkList
	{
		ElemType *data;
		int length, size;

		void ReNew_L();
	}L;
public:
	/*************/
	/*common part*/
	/*************/
	SQList();
	~SQList();
	void reset(const int);

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
	Status Union(const SQList&, const SQList&);

	/********************/
	/*only for unordered*/
	/********************/
	Status insert(const int, const ElemType);
};

void SQList::LinkList::ReNew_L()
{
	ElemType *New = new(nothrow) ElemType[length + Block_L];
	if (New == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
	memcpy(New, data, length * sizeof(ElemType));
	delete[]data;
	data = New;
	length += Block_L;
}

SQList::SQList()
{
	L.data = new(nothrow) ElemType[Initial_L]{0};
	if (L.data == NULL)
		exit(Overflow);
	L.size = Initial_L;
	L.length = 0;
}
SQList::~SQList()
{
	delete[]L.data;
	L.size = L.length = 0;
}
void SQList::reset(const int size)
{
	if (L.size)
	{
		delete[]L.data;
		L.size = L.length = 0;
	}

	L.data = new(nothrow) ElemType[size]{ 0 };
	if (L.data == NULL)
		exit(Overflow);
	L.size = size;
	L.length = 0;
}

Status SQList::clear()
{
	L.length = 0;
	return 0;
}
Status SQList::empty() const
{
	return L.length != 0;
}
int SQList::length() const
{
	return L.length;
}

Status SQList::del(const ElemType x)
{
	sFor(i,0,L.length)
		if (L.data[i] == x)
		{
			sFor(j, i, L.length)
				L.data[j] = L.data[j + 1];
			--L.length;
			return OK;
		}
	return ERROR;
}
Status SQList::del(const int i, ElemType &res)
{
	if (i > L.length || i < 1)
		return ERROR;
	res = L.data[i - 1];
	sFor(j, i - 1, L.length)
		L.data[j] = L.data[j + 1];
	--L.length;
	return OK;
}
Status SQList::del_all(const ElemType x)
{
	Status find = 0;
	sFor(i, 0, L.length)
	{
		if (L.data[i] != x)
			continue;
		find = 1;
		L.data[i] = Lazy;
	}
	if (!find)
		return ERROR;
	int l = 0, r;
	while (L.data[l] != Lazy) ++l; r = l + 1;
	while (r < L.length)
	{
		while (L.data[r] != Lazy && r < L.length)
			L.data[l++] = L.data[r++];
		++r;
	}
	L.length = l;
	return OK;
}
Status SQList::del_same()
{
	const int Maxa = 10000;
	bool f[Maxa + 10] = {0};
	sFor(i, 0, L.length)
		if (!f[L.data[i]])
			f[L.data[i]] = 1;
		else
			L.data[i] = Lazy;
	int l = 0, r;
	while (L.data[l] != Lazy) ++l; r = l + 1;
	while (r < L.length)
	{
		while (L.data[r] != Lazy && r < L.length)
			L.data[l++] = L.data[r++];
		++r;
	}
	L.length = l;
	return OK;
}

Status SQList::search(const ElemType x, int &pos) const
{
	sFor(i, 0, L.length)
		if (L.data[i] == x)
		{
			pos = i + 1;
			return OK;
		}
	return ERROR;
}
Status SQList::reverse()
{
	int l = 0, r = L.length - 1;
	ElemType tmp;
	while (l < r)
		tmp = L.data[l], L.data[l] = L.data[r], L.data[r] = tmp,
		++l, --r;
	return OK;
}
Status SQList::output() const
{
	cout << "=>";
	if (!L.length)
		return ERROR;
	sFor(i, 0, L.length - 1)
		cout << L.data[i] << "=>";
	cout << L.data[L.length-1];
	return OK;
}

Status SQList::insert(const ElemType x)
{
	if (L.length == L.size)
		L.ReNew_L();
	int pos = L.length + 1;
	sFor(i, 0, L.length)
		if (L.data[i] >= x)
		{
			pos = i + 1;
			break;
		}

	opFor(i, L.length - 1, pos - 1)
		L.data[i + 1] = L.data[i];
	L.data[pos - 1] = x;
	++L.length;
	return pos;
}
Status SQList::Union(const SQList &A, const SQList &B)
{
	if (!empty())
		reset(A.L.length + B.L.length + 10);
	sFor(i, 0, A.L.length)
		insert(A.L.data[i]);
	sFor(i, 0, B.L.length)
		insert(B.L.data[i]);

	return OK;
}

Status SQList::insert(const int i, const ElemType x)
{
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length == L.size)
		L.ReNew_L();
	opFor(j, L.length - 1, i - 1)
		L.data[j + 1] = L.data[j];
	L.data[i - 1] = x;
	++L.length;
	return OK;
}

void unordered_test()
{
	SQList L;
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
	SQList LA, LB, LC;
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
