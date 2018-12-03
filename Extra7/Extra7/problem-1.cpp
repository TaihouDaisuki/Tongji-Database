#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)

using namespace std;

void Quick_Sort(int *A, int l, int r)
{
	if (l >= r) return;
	int i = l, j = r, mid = (l + r) >> 1;
	int tmp;
	tmp = A[i]; A[i] = A[mid]; A[mid] = tmp;
	tmp = A[i];
	while (i < j)
	{
		while (i < j && A[j] >= tmp) --j;
		if (i < j) A[i] = A[j], ++i;
		while (i < j && A[i] <= tmp) ++i;
		if (i < j) A[j] = A[i], --j;
	}
	A[i] = tmp;
	Quick_Sort(A, l, i - 1); Quick_Sort(A, i + 1, r);
}

int main()
{
	int n; int *val;

	cin >> n;
	val = new(nothrow) int[n + 1];
	if (val == NULL)
		exit(-1);
	For(i, 1, n)
		cin >> val[i];

	int ans = 0;
	For(i, 2, n)
	{
		Quick_Sort(val, i - 1, n);
		ans += val[i - 1] + val[i];
		val[i] += val[i - 1];
	}
	cout << ans << endl;

	delete[]val;
	//system("pause");
	return 0;
}