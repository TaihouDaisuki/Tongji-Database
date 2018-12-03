#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)

using namespace std;

void push_up(int* const H, int cur)
{
	int tmp;
	while (cur > 1)
	{
		int fa = cur >> 1;
		if (H[fa] <= H[cur])
			break;
		tmp = H[fa]; H[fa] = H[cur]; H[cur] = tmp;
		cur = fa;
	}
}
void push_down(int* const H, int cur, const int p)
{
	int tmp;
	while (cur <= p)
	{
		int lc = cur << 1, rc = cur << 1 | 1;
		if ((lc > p && rc > p) || (H[cur] <= H[lc] && H[cur] <= H[rc]))
			break;
		if (rc > p)
		{
			if (H[cur] > H[lc])
				tmp = H[lc], H[lc] = H[cur], H[cur] = tmp, cur = lc;
			else
				break;
		}
		else
		{
			if ((H[cur] > H[lc]) ^ (H[cur] > H[rc]))
			{
				if (H[lc] < H[cur])
					tmp = H[lc], H[lc] = H[cur], H[cur] = tmp, cur = lc;
				else
					tmp = H[rc], H[rc] = H[cur], H[cur] = tmp, cur = rc;
			}
			else
			{
				if (H[lc] < H[rc])
					tmp = H[lc], H[lc] = H[cur], H[cur] = tmp, cur = lc;
				else
					tmp = H[rc], H[rc] = H[cur], H[cur] = tmp, cur = rc;
			}
		}
	}
}

void Heap_sort(int* const A, const int n)
{
	For(i, 1, n)
		push_up(A, i);
	int tmp;
	For(i, 1, n)
	{
		tmp = A[1]; A[1] = A[n - i + 1]; A[n - i + 1] = tmp;
		push_down(A, 1, n - i);
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	int *A = new(nothrow) int[n + 1];
	if (A == NULL)
		exit(-1);
	For(i, 1, n)
		cin >> A[i];
	Heap_sort(A, n);
	For(i, 1, k)
		cout << A[i]<<' ';
	puts("");

	//system("pause");
	return 0;
}

