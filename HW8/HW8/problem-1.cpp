#include<iostream>
#include<cstdio>
#include<algorithm>

#define For(i,l,r) for(int i = l; i <= r; ++i)
#define sFor(i,l,r) for(int i = l; i < r; ++i)

using namespace std;

int find(const int *const A, const int low, const int high, const int x)
{
	int l = low, r = high;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		A[mid] < x ? l = mid + 1 : r = mid;
	}
	return (A[l] == x) ? l : -1;
}

int main()
{
	int n;
	int *A;
	cin >> n;
	A = new(nothrow) int[n];
	if (A == NULL)
		exit(-1);
	sFor(i, 0, n)
		cin >> A[i];
	int x;
	cin >> x;
	int pos = find(A, 0, n - 1, x);
	cout << pos << endl;

	delete[]A;
	system("pause");
	return 0;
}