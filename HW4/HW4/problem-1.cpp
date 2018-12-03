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

class SQ_Queue
{
private:
	struct Queue
	{
		ElemType *data;
		int head, tail, size;
		Status empty;
	}Q;
public:
	SQ_Queue();
	~SQ_Queue();

	Status reset(const int);

	Status empty() const;
	Status push(const ElemType);
	Status pop(ElemType &);
};

SQ_Queue::SQ_Queue()
{
	Q.head = Q.tail = Q.size = 0;
	Q.empty = 1;
}
SQ_Queue::~SQ_Queue()
{
	delete[]Q.data;
	Q.size = Q.head = Q.tail = 0;
}

Status SQ_Queue::reset(const int size)
{
	Q.data = new(nothrow) ElemType[size];
	if (Q.data == NULL)
		exit(Overflow);
	Q.size = size;
	Q.head = Q.tail = 0;
	Q.empty = 1;
	return OK;
}
Status SQ_Queue::empty()const
{
	return Q.empty;
}
Status SQ_Queue::push(const ElemType x)
{
	if (Q.head == Q.tail && !Q.empty)
		return ERROR;
	Q.data[Q.tail++] = x;
	Q.empty = 0;
	if (Q.tail == Q.size)
		Q.tail = 0;
	return OK;
}
Status SQ_Queue::pop(ElemType &res)
{
	if (Q.head == Q.tail && Q.empty)
		return ERROR;
	res = Q.data[Q.head++];
	if (Q.head == Q.size)
		Q.head = 0;
	if (Q.head == Q.tail)
		Q.empty = 1;
	return OK;
}

int main()
{
	SQ_Queue Q;
	int n;
	cin >> n;
	Q.reset(n);
	while (1)
	{
		char op[15];
		cin >> op;
		if (!strcmp(op, "quit"))
		{
			while (!Q.empty())
			{
				ElemType x;
				Q.pop(x);
				cout << x << ' ';
			}
			puts("");
			break;
		}
		if (!strcmp(op, "dequeue"))
		{
			ElemType x;
			Status res = Q.pop(x);
			if (res == ERROR)
				puts("Queue is Empty");
			else
				cout << x << endl;
			continue;
		}
		// !strcmp(op,"enqueue")
		ElemType x;
		cin >> x;
		Status res = Q.push(x);
		if (res == ERROR)
			puts("Queue is Full");
	}

	//system("pause");
	return 0;
}
