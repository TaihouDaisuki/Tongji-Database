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
	}S;
public:
	SQ_Stack();
	~SQ_Stack();

	Status reset(const int);
	Status empty() const;

	int get_size()const;

	Status push(const ElemType);
	Status pop(ElemType &);
};

SQ_Stack::SQ_Stack()
{
	S.data = NULL;
	S.top = S.size = 0;
}
SQ_Stack::~SQ_Stack()
{
	delete[]S.data;
	S.size = S.top = 0;
}

Status SQ_Stack::reset(const int size)
{
	S.data = new(nothrow) ElemType[size];
	S.size = size;
	S.top = 0;
	return OK;
}
Status SQ_Stack::empty()const
{
	return !S.top;
}

int SQ_Stack::get_size()const
{
	return S.top;
}

Status SQ_Stack::push(const ElemType x)
{
	S.data[S.top++] = x;
	return OK;
}
Status SQ_Stack::pop(ElemType &res)
{
	if (!S.top)
		return ERROR;
	res = S.data[--S.top];
	return OK;
}

int main()
{
	SQ_Stack S;

	int n;
	cin >> n;
	S.reset(n);

	while (1)
	{
		char op[10];
		cin >> op;
		if (!strcmp(op, "quit"))
		{
			ElemType res;
			while (!S.empty())
			{
				S.pop(res);
				cout << res;
				if (!S.empty())
					cout << " ";
				else
					cout << endl;
			}
			break;
		}
		if (!strcmp(op, "push"))
		{
			ElemType x;
			cin >> x;
			if (S.get_size() == n)
				puts("Stack is Full");
			else
				S.push(x);
			continue;
		}
		// op=="pop"
		if (S.empty())
			puts("Stack is Empty");
		else
		{
			ElemType res;
			S.pop(res);
			cout << res << endl;
		}
	}

	//system("pause");
	return 0;
}
