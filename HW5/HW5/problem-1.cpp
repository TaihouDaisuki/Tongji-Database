#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define Default -1
#define Empty -2

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)

using namespace std;

class Binary_Tree
{
private:
	struct Node
	{
		char ch;
		int lc, rc, fa;
	};
	int cnt;
	Node *tr;
public:
	~Binary_Tree();

	void build(const string &);

	void output_fst() const;
	void output_mid() const;
	void output_lst() const;
	void output_bfs() const;
	void output_print() const;
};
Binary_Tree::~Binary_Tree()
{
	delete[]tr;
}

void Binary_Tree::build(const string &s)
{
	int len = s.length(); cnt = 0;
	sFor(i, 0, len)
		cnt += (s[i] != '#');

	tr = new(nothrow) Node[cnt];
	tr[0].fa = Empty; tr[0].lc = tr[0].rc = Default; tr[0].ch = s[0];

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
			tr[cur].rc = cnt; cur = cnt++;
		}
		else
			cur = tr[cur].fa;
	}
}

void Binary_Tree::output_fst() const
{
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
}
void Binary_Tree::output_mid() const
{
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
}
void Binary_Tree::output_lst() const
{
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
}
void Binary_Tree::output_bfs() const
{
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
}
void Binary_Tree::output_print() const
{
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
}

int main()
{
	Binary_Tree tr;
	string ini;
	cin >> ini;

	tr.build(ini);
	tr.output_fst();
	tr.output_mid();
	tr.output_lst();
	tr.output_bfs();
	tr.output_print();

	//system("pause");
	return 0;
}