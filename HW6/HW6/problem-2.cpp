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

	void build_mid();
	void output_mid() const;
	int get_pre(const int) const;
	int get_nxt(const int) const;
public:
	~Binary_Tree();

	void build(const string &);

	void mid_work();
	
	void query_mid(const char) const;
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

void Binary_Tree::build_mid()
{
	int* S = new(nothrow) int[cnt];
	int top = 0, head = 0, pre = Empty;

	while (head != Empty || top)
	{
		while (head != Empty)
			S[top++] = head, head = tr[head].lc;
		int cur = S[--top]; //cout<<tr[cur].ch;
		if (tr[cur].lc == Empty)
			tr[cur].ltag = LINK, tr[cur].lc = pre;
		pre = cur;
		if (tr[cur].rc == Empty)
			tr[cur].rtag = LINK, tr[cur].rc = top ? S[top - 1] : Empty;
		else
			head = tr[cur].rc;
	}
	//puts("");
	delete[]S;
}

void Binary_Tree::output_mid() const
{
	int cur = 0;
	while (cur != Empty)
	{
		while (tr[cur].ltag == NODE)
			cur = tr[cur].lc;
		cout << tr[cur].ch;
		while (tr[cur].rtag == LINK && tr[cur].rc != Empty)
			cur = tr[cur].rc, cout << tr[cur].ch;
		cur = tr[cur].rc;
	}
	puts("");
}

int Binary_Tree::get_pre(const int x) const
{
	if (tr[x].ltag == LINK)
		return tr[x].lc;
	int cur = tr[x].lc;
	while (tr[cur].rtag == NODE)
		cur = tr[cur].rc;
	return cur;
}
int Binary_Tree::get_nxt(const int x) const
{
	if (tr[x].rtag == LINK)
		return tr[x].rc;
	int cur = tr[x].rc;
	while (tr[cur].ltag == NODE)
		cur = tr[cur].lc;
	return cur;
}
void Binary_Tree::query_mid(const char ch) const
{
	int pos = Default;
	sFor(i, 0, cnt)
		if (tr[i].ch == ch)
		{
			pos = i;
			break;
		}
	if (pos == Default)
	{
		puts("Not found");
		return;
	}
	int pre = get_pre(pos), nxt = get_nxt(pos);
	cout << "succ is ";
	if (nxt == Empty)
		puts("NULL");
	else
		cout << tr[nxt].ch << tr[nxt].rtag << endl;
	cout << "prev is ";
	if (pre == Empty)
		puts("NULL");
	else
		cout << tr[pre].ch << tr[pre].ltag << endl;
}

void Binary_Tree::mid_work()
{
	build_mid();
	output_mid();
}

int main()
{
	Binary_Tree tr;
	string ini;
	cin >> ini;

	tr.build(ini);
	tr.mid_work();

	char Q;
	cin >> Q;
	tr.query_mid(Q);

	system("pause");
	return 0;
}