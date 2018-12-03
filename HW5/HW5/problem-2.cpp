#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define Default -1
#define Empty -2

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)
#define Max(a,b) ((a)>(b)?(a):(b))

using namespace std;

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
	~Binary_Tree();

	void build(const string &);

	void reverser();

	void output_base() const;
	void output_print() const;
};
Binary_Tree::~Binary_Tree()
{
	delete[]tr;
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
	tr.output_base();
	tr.output_print();
	tr.reverser();
	tr.output_print();

	//system("pause");
	return 0;
}