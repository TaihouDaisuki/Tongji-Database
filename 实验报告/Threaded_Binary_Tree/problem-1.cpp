#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define Default -1
#define Empty -2
#define NODE 0
#define LINK 1

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)

using namespace std;

class Binary_Tree
{
private:
	struct Node
	{
		char ch;
		int lc, rc, fa, dep;
		int ltag, rtag;
	};
	int cnt;
	Node *tr;

	void build_fst();

	void output_fst() const;
public:
	~Binary_Tree();

	void build(const string &);

	void fst_work();

	void output_print() const;
};
Binary_Tree::~Binary_Tree()
{
	delete[]tr;
}

void Binary_Tree::build(const string &s)
{
	int len = s.length(), dep = 0; cnt = 0;
	sFor(i, 0, len)
		cnt += (s[i] != '#');

	tr = new(nothrow) Node[cnt];
	sFor(i, 0, cnt)
		tr[i].ltag = tr[i].rtag = NODE;
	tr[0].fa = Empty; tr[0].lc = tr[0].rc = Default; tr[0].ch = s[0];
	tr[0].dep = 0;

	cnt = 1;
	int p = 1; int cur = 0;
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
			tr[cnt].dep = ++dep;
			tr[cur].lc = cnt; cur = cnt++;
		}
		else if (tr[cur].rc == Default)//rc
		{
			if (s[p] == '#')
			{
				tr[cur].rc = Empty; ++p;
				cur = tr[cur].fa;
				continue;
			}
			tr[cnt].fa = cur; tr[cnt].lc = tr[cnt].rc = Default; tr[cnt].ch = s[p++];
			tr[cnt].dep = ++dep;
			tr[cur].rc = cnt; cur = cnt++;
		}
		else
			cur = tr[cur].fa, --dep;
	}
}

void Binary_Tree::build_fst()
{
	int* S = new(nothrow) int[cnt];
	int top = 0, pre = Empty;

	S[top++] = 0;
	while (top)
	{
		int cur = S[--top]; //cout<<tr[cur].ch;
		if (tr[cur].rc != Empty)
			S[top++] = tr[cur].rc;
		if (tr[cur].lc != Empty)
			S[top++] = tr[cur].lc;
		else
			tr[cur].ltag = LINK, tr[cur].lc = pre;
		if (pre != Empty && tr[pre].rc == Empty)
			tr[pre].rtag = LINK, tr[pre].rc = cur;
		pre = cur;
	}
	tr[pre].rtag = LINK;
	//puts("");
	delete[]S;
}

void Binary_Tree::output_fst() const
{
	int cur = 0;
	while (cur != Empty)
	{
		cout << tr[cur].ch;
		if (tr[cur].ltag == NODE)
			cur = tr[cur].lc;
		else
			cur = tr[cur].rc;
	}
	puts("");
}

void Binary_Tree::output_print() const
{
	int* S = new(nothrow) int[cnt + 1];
	int top = 0, pre = Default, dep = 0;

	S[top++] = 0;
	while (top)
	{
		int cur = S[top - 1];
		if (tr[cur].rtag == NODE && pre == tr[cur].rc)
		{
			For(i, 1, dep * 5) cout << ' ';	
			cout << tr[cur].ch << tr[cur].ltag << tr[cur].rtag << endl;
			if (tr[cur].ltag == NODE)
				S[top++] = tr[cur].lc, ++dep;
			else
				pre = cur, --top, --dep;
		}
		else if (tr[cur].ltag == NODE && pre == tr[cur].lc)
			pre = cur, --top, --dep;
		else if (tr[cur].rtag == NODE)
			S[top++] = tr[cur].rc, ++dep;
		else if (tr[cur].ltag == NODE)
		{
			For(i, 1, dep * 5) cout << ' ';
			cout << tr[cur].ch << tr[cur].ltag << tr[cur].rtag << endl;
			S[top++] = tr[cur].lc, ++dep;
		}
		else
		{
			For(i, 1, dep * 5) cout << ' ';
			cout << tr[cur].ch << tr[cur].ltag << tr[cur].rtag << endl;
			pre = cur, --top, --dep;
		}
	}
	delete[]S;
}

void Binary_Tree::fst_work()
{
	build_fst();
	output_print();
	output_fst();
}

int main()
{
	Binary_Tree tr;
	string ini;
	cin >> ini;

	tr.build(ini);
	tr.fst_work();

	//system("pause");
	return 0;
}