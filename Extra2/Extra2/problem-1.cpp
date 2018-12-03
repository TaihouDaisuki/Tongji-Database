#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define For(i,l,r) for(int i=l;i<=r;++i)

using namespace std;

int main()
{
	int n, s, m;
	int tot_out = 0;
	cin >> n >> s >> m;
	int *nxt = new(nothrow) int[n + 1];
	For(i, 1, n - 1)
		nxt[i] = i + 1;
	nxt[n] = 1;
	int cur = s, pre = (s == 1 ? n : s - 1);
	while (tot_out<n)
	{
		int cnt = 1;
		while (cnt<m)
			pre = cur, cur = nxt[cur], ++cnt;
		cout << cur << ' '; ++tot_out;
		nxt[pre] = nxt[cur]; cur = nxt[cur];
	}
	puts("");
	delete[]nxt;
	//system("pause");
	return 0;
}
