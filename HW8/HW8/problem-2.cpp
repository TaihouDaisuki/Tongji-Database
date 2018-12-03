#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>

#define For(i,l,r) for(int i = l; i <= r; ++i)
#define sFor(i,l,r) for(int i = l; i < r; ++i)
#define opFor(i,r,l) for(int i = r; i >= l; --i)

using namespace std;

class Bin_Sort_Tree
{
private:
	struct Node
	{
		int x;
		Node *lc, *rc;
		Node() { lc = rc = NULL; }
		Node(const int _x) { x = _x; lc = rc = NULL; }
	};
	int tot;
	Node *root;

	void del_work(Node*&);
public:
	Bin_Sort_Tree();
	~Bin_Sort_Tree();

	bool search(Node* const, const int, Node*&) const;
	bool insert(const int);
	bool del(const int);

	void output_fst() const;
	void calc_ave() const;
};

Bin_Sort_Tree::Bin_Sort_Tree()
{
	tot = 1;
	root = new(nothrow) Node(2147483647);
}
Bin_Sort_Tree::~Bin_Sort_Tree()
{
	Node **Q = new(nothrow)Node*[tot];
	int l = 0, r = 0;
	Q[r++] = root;
	while (l < r)
	{
		Node* cur = Q[l++];
		if (cur->lc != NULL)
			Q[r++] = cur->lc;
		if (cur->rc != NULL)
			Q[r++] = cur->rc;
	}
	opFor(i, r - 1, 0)
		delete Q[i];
	delete[]Q;
	root = NULL;
	tot = 0;
}

bool Bin_Sort_Tree::search(Node* const tRoot, const int x, Node* &p) const
{
	Node* cur = tRoot, *pre = tRoot;
	while (cur != NULL)
	{
		if (cur->x == x)
			break;
		pre = cur;
		cur = x < cur->x ? cur->lc : cur->rc;
	}
	return cur == NULL ? (p = pre, 0) : (p = cur, 1);
}

bool Bin_Sort_Tree::insert(const int x)
{
	Node* pre;
	if (!search(root, x, pre))
	{
		Node *cur = new(nothrow) Node(x);
		if (cur == NULL)
			return 0;
		if (cur->x < pre->x)
			pre->lc = cur;
		else
			pre->rc = cur;
		++tot;
	}
	else
		return 0;
	return 1;
}

void Bin_Sort_Tree::del_work(Node* &p)
{
	if (p->lc == NULL && p->rc == NULL)
	{
		delete p;
		p = NULL;
	}
	else if (p->rc == NULL)
	{
		Node* q = p;
		p = p->lc;
		delete q;
	}
	else if (p->lc == NULL)
	{
		Node* q = p;
		p = p->rc;
		delete q;
	}
	else
	{
		Node *pre = p, *cur = pre->lc;
		while (cur->rc != NULL)
			pre = cur, cur = cur->rc;
		p->x = cur->x;
		if (pre != p)
			pre->rc = cur->lc;
		else
			pre->lc = cur->lc;
		delete cur;
	}
}
bool Bin_Sort_Tree::del(const int x)
{
	Node* cur = root, *pre = NULL;
	while (cur != NULL)
	{
		if (cur->x == x)
			break;
		pre = cur;
		cur = x < cur->x ? cur->lc : cur->rc;
	}
	if (cur == NULL)
		return 0;
	if (pre->lc->x == x)
		del_work(pre->lc);
	else
		del_work(pre->rc);
	--tot;
	return 1;
}

void Bin_Sort_Tree::output_fst() const
{
	Node**S = new(nothrow) Node*[tot];
	int top = 0;
	if (root->lc == NULL)
	{
		puts("");
		delete[]S;
		return;
	}
	S[top++] = root->lc;
	while (top)
	{
		Node* cur = S[--top];
		if (cur->rc != NULL)
			S[top++] = cur->rc;
		if (cur->lc != NULL)
			S[top++] = cur->lc;
		cout << cur->x << ' ';
	}
	puts("");
	delete[]S;
}

void Bin_Sort_Tree::calc_ave() const
{
	Node **Q = new(nothrow)Node*[tot];
	int* dep = new(nothrow) int[tot];
	double ans = 0;
	int l = 0, r = 0;
	Q[r++] = root; dep[0] = 0;
	while (l < r)
	{
		Node* cur = Q[l]; ans += dep[l];
		if (cur->lc != NULL)
			Q[r] = cur->lc, dep[r++] = dep[l] + 1;
		if (cur->rc != NULL)
			Q[r] = cur->rc, dep[r++] = dep[l] + 1;
		++l;
	}
	ans /= tot - 1;
	cout.setf(ios::fixed);
	cout << fixed << setprecision(2) << ans << endl;
	cout.unsetf(ios::fixed);
	delete[]Q;
	delete[]dep;
}

int main()
{
	int n;
	cin >> n;
	Bin_Sort_Tree tr;
	int x;
	For(i, 1, n)
	{
		cin >> x;
		tr.insert(x);
	}
	cin >> x;
	bool res = tr.del(x);
	cout << res << endl;
	res = tr.insert(x);
	cout << (res ^ 1) << endl;
	tr.output_fst();
	tr.calc_ave();
	system("pause");
	return 0;
}