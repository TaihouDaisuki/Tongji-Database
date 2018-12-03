#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define sFor(i,l,r) for(int i=l;i<r;++i)

using namespace std;

int main()
{
	int n, m;
	int *(p[3]), *(e[3]);
	int cnt = 0;

	cin >> m;
	p[0] = new(nothrow) int[m];
	e[0] = new(nothrow) int[m];
	sFor(i, 0, m)
		cin >> p[0][i] >> e[0][i];

	cin >> n;
	p[1] = new(nothrow)int[n];
	e[1] = new(nothrow)int[n];
	sFor(i, 0, n)
		cin >> p[1][i] >> e[1][i];

	p[2] = new(nothrow)int[n + m];
	e[2] = new(nothrow)int[n + m];

	int p1 = 0, p2 = 0;
	while (p1 < m && p2 < n)
	{
		if (e[0][p1] == e[1][p2])
		{
			p[2][cnt] = p[0][p1] + p[1][p2];
			e[2][cnt] = e[0][p1];
			++cnt; ++p1; ++p2;
			continue;
		}
		if (e[0][p1] < e[1][p2])
			p[2][cnt] = p[0][p1], e[2][cnt] = e[0][p1], ++p1;
		else
			p[2][cnt] = p[1][p2], e[2][cnt] = e[1][p2], ++p2;
		++cnt;
	}
	while(p1<m)
		p[2][cnt] = p[0][p1], e[2][cnt] = e[0][p1], ++p1, ++cnt;
	while(p2<n)
		p[2][cnt] = p[1][p2], e[2][cnt] = e[1][p2], ++p2, ++cnt;
	sFor(i, 0, cnt)
		if(p[2][i])
			cout << p[2][i] << ' ' << e[2][i] << endl;
	sFor(i, 0, 3)
	{
		delete[]e[i];
		delete[]p[i];
	}

	//system("pause");
	return 0;
}