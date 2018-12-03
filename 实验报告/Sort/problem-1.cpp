#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)

using namespace std;

template<class cmpType>
int default_cmp(cmpType x, cmpType y)
{
	return x < y;
}
template<class sortType>
void Quick_sort(sortType *low, sortType *high, int(*cmp)(sortType, sortType) = default_cmp)
{
	sortType *l = low, *r = high - 1;
	if (l >= r)
		return;
	sortType *mid; mid = l + (int(r - l) >> 1);
	sortType tmp = *mid; *mid = *low; *low = tmp;
	while (l < r)
	{
		while (l < r && cmp(tmp, *r)) --r;
		if (l < r) *l = *r, ++l;
		while (l < r && cmp(*l, tmp)) ++l;
		if (l < r) *r = *l, --r;
	}
	*l = tmp;
	Quick_sort(low, l, cmp); Quick_sort(l + 1, high, cmp);
}
template<class sortType, class Func>
void Quick_sort(sortType *low, sortType *high, Func(*cmp)(sortType, sortType) = default_cmp)
{
	sortType *l = low, *r = high - 1;
	if (l >= r)
		return;
	sortType *mid; mid = l + (int(r - l) >> 1);
	sortType tmp = *mid; *mid = *low; *low = tmp;
	while (l < r)
	{
		while (l < r && cmp(tmp, *r)) --r;
		if (l < r) *l = *r, ++l;
		while (l < r && cmp(*l, tmp)) ++l;
		if (l < r) *r = *l, --r;
	}
	*l = tmp;
	Quick_sort(low, l, cmp); Quick_sort(l + 1, high, cmp);
}

bool cmp(const int A, const int B)
{
	return A > B;
}
//从大到小排序时使用的比较函数

int main()
{
	int n;
	cin >> n;
	int *A = new(nothrow) int[n];
	if (A == NULL)
		exit(-1);
	sFor(i, 0, n)
		cin >> A[i];
	Quick_sort(A, A + n);
	//Quick_sort(A, A + n, cmp); //重载快排，cmp为比较函数，前两个参数为左闭右开区间
	sFor(i, 0, n)
		cout << A[i] << ' ';
	puts("");

	//system("pause");
	return 0;
}
