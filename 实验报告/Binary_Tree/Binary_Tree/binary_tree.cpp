#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<conio.h>

#define Default -1
#define Empty -2
#define OK 1
#define ERROR 0

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)
#define Max(a,b) ((a)>(b)?(a):(b))

using namespace std;

typedef bool Status;

class Binary_Tree
{
private:
	struct Node
	{
		char ch;
		int lc, rc, fa;
	};
	int cnt, cnt_leaf, dep;
	Node *tr;
public:
	Binary_Tree();
	~Binary_Tree();

	void build(const string &);

	void clear();
	void reverser();

	void output_base() const;
	Status output_fst() const;
	Status output_mid() const;
	Status output_lst() const;
	Status output_bfs() const;
	Status output_print() const;
};
Binary_Tree::Binary_Tree()
{
	tr = NULL;
	cnt = cnt_leaf = dep = 0;
}
Binary_Tree::~Binary_Tree()
{
	delete[]tr;
}
void Binary_Tree::clear()
{
	if (tr != NULL)
		delete[]tr;
	tr = NULL;
	cnt = cnt_leaf = dep = 0;
}

void Binary_Tree::build(const string &s)
{
	cnt = dep = cnt_leaf = 0;
	int len = s.length();
	sFor(i, 0, len)
		cnt += (s[i] != '#');

	tr = new(nothrow) Node[cnt];
	tr[0].fa = Empty; tr[0].lc = tr[0].rc = Default; tr[0].ch = s[0];

	cnt = 1;
	int p = 1; int cur = 0, cur_dep = 1;
	while (p < len)
	{
		if (tr[cur].lc == Default) //lc
		{
			if (s[p] == '#')
			{
				tr[cur].lc = Empty; ++p;
				continue;
			}
			tr[cnt].fa = cur; tr[cnt].lc = tr[cnt].rc = Default; tr[cnt].ch = s[p++];
			tr[cur].lc = cnt; cur = cnt++;
			++cur_dep;  dep = Max(cur_dep, dep);
		}
		else if (tr[cur].rc == Default)//rc
		{
			if (s[p] == '#')
			{
				if (tr[cur].lc == Empty)
					++cnt_leaf;
				tr[cur].rc = Empty; ++p;
				cur = tr[cur].fa; --cur_dep;
				continue;
			}
			tr[cnt].fa = cur; tr[cnt].lc = tr[cnt].rc = Default; tr[cnt].ch = s[p++];
			tr[cur].rc = cnt; cur = cnt++;
			++cur_dep; dep = Max(cur_dep, dep);
		}
		else
			cur = tr[cur].fa, --cur_dep;
	}
}

void Binary_Tree::reverser()
{
	int tmp;
	sFor(i, 0, cnt)
		tmp = tr[i].lc, tr[i].lc = tr[i].rc, tr[i].rc = tmp;
}

void Binary_Tree::output_base() const
{
	cout << cnt_leaf << endl;
	cout << cnt << endl;
	cout << dep << endl;
}
Status Binary_Tree::output_fst() const
{
	if (tr == NULL)
		return ERROR;
	int* S = new(nothrow) int[cnt];
	int top = 0, pre = Default;

	S[top++] = 0; cout << tr[0].ch;
	while (top)
	{
		int cur = S[top - 1];
		if (pre == tr[cur].lc)
		{
			if (tr[cur].rc != Empty)
				S[top++] = tr[cur].rc, cout << tr[tr[cur].rc].ch;
			else
				pre = cur, --top;
		}
		else if (pre == tr[cur].rc)
			pre = cur, --top;
		else if (tr[cur].lc != Empty)
			S[top++] = tr[cur].lc, cout << tr[tr[cur].lc].ch;
		else if (tr[cur].rc != Empty)
			S[top++] = tr[cur].rc, cout << tr[tr[cur].rc].ch;
		else
			pre = cur, --top;
	}

	puts("");
	delete[]S;
	return OK;
}
Status Binary_Tree::output_mid() const
{
	if (tr == NULL)
		return ERROR;
	int* S = new(nothrow) int[cnt + 1];
	int top = 0, pre = Default;

	S[top++] = 0;
	while (top)
	{
		int cur = S[top - 1];
		if (pre == tr[cur].lc)
		{
			cout << tr[cur].ch;
			if (tr[cur].rc != Empty)
				S[top++] = tr[cur].rc;
			else
				pre = cur, --top;
		}
		else if (pre == tr[cur].rc)
			pre = cur, --top;
		else if (tr[cur].lc != Empty)
			S[top++] = tr[cur].lc;
		else if (tr[cur].rc != Empty)
			cout << tr[cur].ch, S[top++] = tr[cur].rc;
		else
			cout << tr[cur].ch, pre = cur, --top;
	}

	puts("");
	delete[]S;
	return OK;
}
Status Binary_Tree::output_lst() const
{
	if (tr == NULL)
		return ERROR;
	int* S = new(nothrow) int[cnt];
	int top = 0, pre = Default;

	S[top++] = 0;
	while (top)
	{
		int cur = S[top - 1];
		if (pre == tr[cur].lc)
		{
			if (tr[cur].rc != Empty)
				S[top++] = tr[cur].rc;
			else
				cout << tr[cur].ch, pre = cur, --top;
		}
		else if (pre == tr[cur].rc)
			cout << tr[cur].ch, pre = cur, --top;
		else if (tr[cur].lc != Empty)
			S[top++] = tr[cur].lc;
		else if (tr[cur].rc != Empty)
			S[top++] = tr[cur].rc;
		else
			cout << tr[cur].ch, pre = cur, --top;
	}

	puts("");
	delete[]S;
	return OK;
}
Status Binary_Tree::output_bfs() const
{
	if (tr == NULL)
		return ERROR;
	int* Q = new(nothrow) int[cnt];
	int l = 0, r = 0;
	Q[r++] = 0;
	while (l < r)
	{
		int cur = Q[l++];
		cout << tr[cur].ch;
		if (tr[cur].lc != Empty)
			Q[r++] = tr[cur].lc;
		if (tr[cur].rc != Empty)
			Q[r++] = tr[cur].rc;
	}
	puts("");
	delete[] Q;
	return OK;
}
Status Binary_Tree::output_print() const
{
	if (tr == NULL)
		return ERROR;
	int* S = new(nothrow) int[cnt + 1];
	int top = 0, pre = Default, dep = 0;

	S[top++] = 0;
	while (top)
	{
		int cur = S[top - 1];
		if (pre == tr[cur].rc)
		{
			For(i, 1, dep * 5) cout << ' ';	cout << tr[cur].ch << endl;
			if (tr[cur].lc != Empty)
				S[top++] = tr[cur].lc, ++dep;
			else
				pre = cur, --top, --dep;
		}
		else if (pre == tr[cur].lc)
			pre = cur, --top, --dep;
		else if (tr[cur].rc != Empty)
			S[top++] = tr[cur].rc, ++dep;
		else if (tr[cur].lc != Empty)
		{
			For(i, 1, dep * 5) cout << ' ';	cout << tr[cur].ch << endl;
			S[top++] = tr[cur].lc, ++dep;
		}
		else
		{
			For(i, 1, dep * 5) cout << ' ';	cout << tr[cur].ch << endl;
			pre = cur, --top, --dep;
		}
	}
	delete[]S;
	return OK;
}

void test_part()
{
#define Pause while(_getch()!='\r')
	puts("/************************/");
	puts("/*对二叉树剧本操作的测试*/");
	puts("/************************/");
	puts("");

	Binary_Tree tr;
	puts("请输入树的先序遍历，空节点以#表示");
	string ini;
	cin >> ini;
	tr.build(ini);
	puts("树建立完成，请按回车键继续...");
	Pause; puts(""); puts("");

	puts("树的遍历:");
	cout << "树的先序遍历为: "; tr.output_fst();
	cout << "树的中序遍历为: "; tr.output_mid();
	cout << "树的后序遍历为: "; tr.output_lst();
	cout << "树的逐层遍历为: "; tr.output_bfs();
	puts("树的遍历结束，请按回车键继续...");
	Pause; puts(""); puts("");

	puts("树的叶子节点个数、节点个数、层数分别为: "); 
	tr.output_base();
	puts("树的打印如下");
	tr.output_print();
	puts("树复制后打印如下");
	tr.reverser();
	tr.output_print();
	puts("测试结束，请按回车键继续...");
	Pause; puts(""); puts("");
}

int main()
{
	/*test_part*/
	test_part();
	/***********/

	return 0;
}