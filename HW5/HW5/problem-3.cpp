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

	void output_mid() const;
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

void Binary_Tree::output_mid() const
{
	int* S = new(nothrow) int[cnt + 1];
	int top = 0, pre = Default;

	S[top++] = 0; cout << "push " << tr[0].ch << endl;
	while (top)
	{
		int cur = S[top - 1];
		if (pre == tr[cur].lc)
		{
			cout << "pop" << endl << tr[cur].ch << endl;
			if (tr[cur].rc != Empty)
			{
				S[top++] = tr[cur].rc;
				cout << "push " << tr[tr[cur].rc].ch << endl;
			}
			else
				pre = cur, --top;
		}
		else if (pre == tr[cur].rc)
			pre = cur, --top;
		else if (tr[cur].lc != Empty)
		{
			S[top++] = tr[cur].lc;
			cout << "push " << tr[tr[cur].lc].ch << endl;
		}
		else if (tr[cur].rc != Empty)
		{
			cout << "pop" << endl << tr[cur].ch << endl;
			S[top++] = tr[cur].rc;
			cout << "push " << tr[tr[cur].rc].ch << endl;
		}
		else
		{
			cout << "pop" << endl << tr[cur].ch << endl;
			pre = cur, --top;
		}
	}

	puts("");
	delete[]S;
}

int main()
{
	Binary_Tree tr;
	string ini;
	cin >> ini;

	tr.build(ini);
	tr.output_mid();

	//system("pause");
	return 0;
}