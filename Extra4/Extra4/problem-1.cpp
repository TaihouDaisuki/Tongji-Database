#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)

using namespace std;

typedef int ElemType;

const int Maxn = 30;



class Stack
{
private:
	int top;
	ElemType s[Maxn];
public:
	Stack();
	void push(const ElemType);
	ElemType pop();
	bool empty();
};

Stack::Stack()
{
	top = 0;
}

void Stack::push(const ElemType x)
{
	s[++top] = x;
}

ElemType Stack::pop()
{
	return s[top--];
}

bool Stack::empty()
{
	return !top;
}

void dfs(int k, char *const s, const int len, int *const ans, int &tail, Stack &stack)
{
	if (k == len + 1 && stack.empty())
	{
		For(i, 1, len)
			printf("%c", s[ans[i]]);
		puts("");
		return;
	}
	if (!stack.empty())
	{
		ans[++tail] = stack.pop();
		dfs(k, s, len, ans, tail, stack);
		stack.push(ans[tail--]);
	}
	if (k <= len)
	{
		stack.push(k);
		dfs(k + 1, s, len, ans, tail, stack);
		stack.pop();
	}
}

int main()
{
	char s[Maxn];
	int ans[Maxn], tail;
	int len;
	Stack stack;

	scanf(" %s", s+1);
	len = strlen(s + 1);
	tail = 0;
	dfs(1, s, len, ans, tail, stack);

	//system("pause");
	return 0;
}