#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define Overflow 2
#define Initial_L 1000 /////////////////////////
#define Block_L 100

using namespace std;

typedef int Status;
typedef int ElemType;

class SQ_Stack
{
private:
	struct Stack
	{
		ElemType *data;
		int top, size;

		void ReNew_S();
	}S;
public:
	SQ_Stack();
	~SQ_Stack();
	Status clear();

	Status empty() const;
	Status push(const ElemType);
	ElemType pop();
	ElemType top();
};
void SQ_Stack::Stack::ReNew_S()
{
	ElemType *New = new(nothrow) ElemType[size + Block_L];
	if (New == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
	memcpy(New, data, size * sizeof(ElemType));
	delete[]data;
	data = New;
	size += Block_L;
}
SQ_Stack::SQ_Stack()
{
	S.data = new(nothrow) ElemType[Initial_L]{ 0 };
	if (S.data == NULL)
		exit(Overflow);
	S.size = Initial_L;
	S.top = 0;
}
SQ_Stack::~SQ_Stack()
{
	delete[]S.data;
	S.size = S.top = 0;
}
Status SQ_Stack::clear()
{
	S.top = 0;
	return OK;
}
Status SQ_Stack::empty()const
{
	return !S.top;
}
Status SQ_Stack::push(const ElemType x)
{
	if (S.top == S.size)
		S.ReNew_S();
	S.data[S.top++] = x;
	return OK;
}
ElemType SQ_Stack::pop()
{
	if (!S.top)
		return 2147483647;
	return S.data[--S.top];
}
ElemType SQ_Stack::top()
{
	if (!S.top)
		return 2147483647;
	return S.data[S.top - 1];
}

int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
	SQ_Stack S;
	char ch; bool fail = 0;
	while ((ch = getchar()) != EOF)
	{
		if (ch != '(' && ch != ')' && ch != '{' && ch != '}' && ch != '[' && ch != ']')
			continue;
		if (ch == '{')
			S.push(1);
		else if (ch == '[')
			S.push(2);
		else if (ch == '(')
			S.push(3);
		else if (ch == '}')
		{
			if (S.empty() || S.top() != 1)
			{
				if (S.empty())
					puts("no"), puts("}ÆÚ´ý×óÀ¨ºÅ"), fail = 1;
				break;
			}
			S.pop();
		}
		else if (ch == ']')
		{
			if (S.empty() || S.top() != 2)
			{
				if (S.empty())
					puts("no"), puts("]ÆÚ´ý×óÀ¨ºÅ"), fail = 1;
				break;
			}
			S.pop();
		}
		else if (ch == ')')
		{
			if (S.empty() || S.top() != 3)
			{
				if (S.empty())
					puts("no"), puts(")ÆÚ´ý×óÀ¨ºÅ"), fail = 1;
				break;
			}
			S.pop();
		}
	}
	if (!fail && S.empty())
		puts("yes");
	else if (!fail)
	{
		puts("no");
		int last = S.top();
		char ans = last == 1 ? '{' : (last == 2 ? '[' : '(');
		cout << ans << "ÆÚ´ýÓÒÀ¨ºÅ" << endl;
	}

	//system("pause");
	return 0;
}
