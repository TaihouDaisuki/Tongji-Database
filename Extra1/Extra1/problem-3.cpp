#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cmath>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define Overflow 2

#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)

using namespace std;

struct ElemType
{
	int p, e;
};

double Pow(double a, int x)
{
	double res = 1, tmp = a;
	while (x)
	{
		if (x & 1)
			res *= tmp;
		x >>= 1;
		tmp *= tmp;
	}
	return res;
}

int main()
{
	int n;
	cin >> n;
	ElemType *Poly = new(nothrow) ElemType[n];
	sFor(i, 0, n)
		cin >> Poly[i].p >> Poly[i].e;
	double x;
	cin >> x;
	double ans = 0;
	sFor(i, 0, n)
		ans += Pow(x, Poly[i].e)*Poly[i].p;
	printf("%.1lf\n", ans);
	
	//system("pause");
	return 0;
}
