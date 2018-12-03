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
#define Initial_L 1000
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
	Status pop(ElemType &);
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
	S.data = new(nothrow) ElemType[Initial_L];
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
	int n, m;
	char num[1010];
	int x = 0;
	cin >> n >> m;
	cin >> num;
	int len = strlen(num);
	for (int i = 0; i<len; ++i)
	{
		x *= n;
		if (num[i] >= '0' && num[i] <= '9')
			x += num[i] - '0';
		else // (num[i]>='A' && num[i]<='Z')
			x += num[i] - 'A' + 10;
	}

	while (x)
	{
		S.push(x%m);
		x /= m;
	}

	while (!S.empty())
	{
		int res;
		S.pop(res);
		if (res <= 9)
			cout << char(res + '0');
		else
			cout << char(res - 10 + 'A');
	}
	puts("");


	//system("pause");
	return 0;
}
